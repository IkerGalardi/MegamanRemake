#include "application.hh"

#include <iostream>

#include <GL/glew.h>

#include "opengl/gl.hh"

namespace engine {
        application::application(const std::string& name) 
            : name(name) 
        {
            SDL_Init(SDL_INIT_EVERYTHING);

            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }

        application::~application() {
            if(opengl_context != nullptr)
                SDL_GL_DeleteContext(opengl_context);

            if(window_handler != nullptr)
                SDL_DestroyWindow(window_handler);

            SDL_Quit();
        }

        void application::start() {
            window_handler = SDL_CreateWindow(name.c_str(), 
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                              700, 700,
                                              SDL_WINDOW_OPENGL);

            opengl_context = SDL_GL_CreateContext(window_handler);
            SDL_GL_MakeCurrent(window_handler, opengl_context);

            auto gl_init_status = glewInit();
            if(gl_init_status != GLEW_OK) {
                std::cerr << "Error loading opengl" << std::endl;
                std::exit(1);
            }

            gl::set_clear_color({0.1, 0.1, 1, 1});

            bool running = true;
            while(running) {
                SDL_GL_SwapWindow(window_handler);
                gl::clear(GL_COLOR_BUFFER_BIT);

                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                    if(event.type == SDL_QUIT) {
                        running = false;
                    }
                }
            }
        }
}