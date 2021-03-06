#pragma once 

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include "system/system.hh"
#include "ecs/scene.hh"
#include "logger.hh"
#include "input/keyboard.hh"

namespace engine {
    class application {
        friend class engine::system;
    public:
        void start();

        template<typename sys>
        std::shared_ptr<sys> attach_system() {
            std::string sys_name = sys::get_name();
            logger->info("System {} has been attatched", sys_name);

            auto system_logger = logger::create_from_name(sys_name);
            
            auto system = std::make_shared<sys>(system_logger);
            attached_systems.push_back(system);
            
            return system;
        }

        void attach_scene(std::function<void(scene&)> bootstrap, const std::string& name);

        inline engine::keyboard& keyboard() { return kb; }

        static application& get();
    private:
        application(const std::string& name = "");
        ~application();


        const std::string name;

        SDL_Window* window_handler;
        SDL_GLContext opengl_context;

        std::vector<std::shared_ptr<engine::system>> attached_systems;

        std::vector<std::function<void(scene&)>> scenes;
        std::shared_ptr<engine::scene> active_scene;

        std::shared_ptr<spdlog::logger> logger;

        engine::keyboard kb;
    protected:
    };
}