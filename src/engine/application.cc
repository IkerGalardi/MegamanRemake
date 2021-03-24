#include "application.hh"

#include <iostream>

#include <GL/glew.h>

#include "logger.hh"

namespace engine
{
    application::application(const std::string &name)
        : name(name)
    {
        logger = logger::create_from_name("app");

        SDL_Init(SDL_INIT_EVERYTHING);
        logger->info("SDL initialized");

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        logger->info("Screen framebuffers initialized");

        // Create the window with undefined position, this way the application should
        // be opened where the the user closed it last
        window_handler = SDL_CreateWindow(name.c_str(),
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          700, 700,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        opengl_context = SDL_GL_CreateContext(window_handler);
        SDL_GL_MakeCurrent(window_handler, opengl_context);
        logger->info("Created window and OpenGL context");

        // Initialize opengl
        auto gl_init_status = glewInit();
        if (gl_init_status != GLEW_OK) {
            logger->critical("Error initializing OpenGL: {}", gl_init_status);
            std::exit(1);
        }
        logger->info("OpenGL initialized succesfully");
    }

    application::~application() {
        // Destroy all the systems (necessary to call the destructor)
        attached_systems.clear();

        // If a OpenGL context exists, destroy it. The context might not exist
        // because application initialization might fail before the actual context
        // is created
        if (opengl_context != nullptr)
            SDL_GL_DeleteContext(opengl_context);

        // Same as with the OpenGL context, the handler might not exist, so before
        // deleting, check if its a valid window
        if (window_handler != nullptr)
            SDL_DestroyWindow(window_handler);

        SDL_Quit();
    }

    void application::start() {
        // If the scene vector is empty, error out
        // Else, add the first scene from the vector as the active scene
        if(scenes.empty()) {
            logger->error("The current scene is not set");
            return;
        } else {
            active_scene = std::make_shared<engine::scene>(logger::create_from_name("active_scene"));
            scenes[0](*active_scene);
        }

        // Send this event at the start, so that all the systems that need to know
        // about the screen resolution can know
        for(auto& system : attached_systems) {
            system->on_screen_resize(700, 700);
        }

        // The main loop. Here events from SDL are thrown into the systems
        // and scenes.
        bool running = true;
        while (running) {
            SDL_GL_SwapWindow(window_handler);

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                // If the event is a SDL_QUIT event, stop executing 
                // the engine
                if (event.type == SDL_EventType::SDL_QUIT) {
                    running = false;

                // If the event is a SDL_WINDOWEVENT, further check if
                // the window size has been changed. If thats true, notify
                // all the systems
                } else if (event.type == SDL_EventType::SDL_WINDOWEVENT) {
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        for(auto& system : attached_systems) {
                            system->on_screen_resize(event.window.data1, 
                                                     event.window.data2);
                        }
                    }
                }
            }

            // Call 'on_update' on all the systems
            for (auto &system : attached_systems) {
                system->on_update();
            }
        }
    }

    void application::attach_scene(std::function<void(scene&)> bootstrap, const std::string& name) {
        scenes.push_back(bootstrap);
        logger->info("scene {} has been added", name);
    }
    
    application& application::get() {
        static application* app = nullptr;
        if(app == nullptr)
            app = new application();

        return *app;
    }
}