#include "application.hh"

#include <iostream>

#include <GL/glew.h>

namespace engine {
        application::application(const std::string& name) 
            : name(name) 
        {
            SDL_Init(SDL_INIT_EVERYTHING);
            std::cout << "SDL initialized" << std::endl;

            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            std::cout << "Setup of opengl framebuffer attributes" << std::endl;

            // Create window
            window_handler = SDL_CreateWindow(name.c_str(), 
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                              700, 700,
                                              SDL_WINDOW_OPENGL);

            opengl_context = SDL_GL_CreateContext(window_handler);
            SDL_GL_MakeCurrent(window_handler, opengl_context);
            std::cout << "Window created with OpenGL context" << std::endl;

            // Initialize opengl
            auto gl_init_status = glewInit();
            if(gl_init_status != GLEW_OK) {
                std::cerr << "Error loading opengl" << std::endl;
                std::exit(1);
            }
            std::cout << "OpenGL initialized" << std::endl;
        }

        application::~application() {
            for(auto& system : attached_systems) {
                system->on_destroy();
            }

            if(opengl_context != nullptr)
                SDL_GL_DeleteContext(opengl_context);

            if(window_handler != nullptr)
                SDL_DestroyWindow(window_handler);

            SDL_Quit();
        }

        void application::start() {
            bool running = true;
            while(running) {
                SDL_GL_SwapWindow(window_handler);

                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                    if(event.type == SDL_QUIT) {
                        running = false;
                    }
                }

                for(auto& system : attached_systems) {
                    system->on_update();
                }
            }
        }
}