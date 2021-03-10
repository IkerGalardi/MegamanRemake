#pragma once 

#include <string>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include "system/system.hh"
#include "logger.hh"

namespace engine {
    class application {
    public:
        application(const std::string& name);
        ~application();

        void start();

        template<typename sys>
        void attach_system() {
            auto logger = logger::create_from_name(sys::get_name());
            attached_systems.push_back(std::make_shared<sys>(*this, logger));
        }
    private:
        const std::string name;

        SDL_Window* window_handler;
        SDL_GLContext opengl_context;

        std::vector<std::shared_ptr<engine::system>> attached_systems;
        std::shared_ptr<spdlog::logger> logger;
    protected:
    };
}