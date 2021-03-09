#pragma once 

#include <string>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "system/system.hh"

namespace engine {
    class application {
    public:
        application(const std::string& name);
        ~application();

        void start();

        template<typename sys>
        void attach_system() {
            attached_systems.push_back(new sys(*this));
        }
    private:
        const std::string name;

        SDL_Window* window_handler;
        SDL_GLContext opengl_context;

        std::vector<engine::system*> attached_systems;
    protected:
    };
}