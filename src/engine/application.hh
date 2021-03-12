#pragma once 

#include <string>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include "system/system.hh"
#include "scene/scene.hh"
#include "logger.hh"

namespace engine {
    class application {
    public:
        application(const std::string& name);
        ~application();

        void start();

        template<typename sc>
        void push_scene(const std::string& name) {
            auto scene = std::make_shared<engine::scene>(name, *this);

            // Push back to the scene to the scene list
            scenes.push_back(scene);

            logger->info("added scene {} to the list", name);

            // There is no active scene, set the current one to active
            if(active_scene.get() == nullptr) {
                active_scene = scene;
                logger->info("{} set to active scene", name);
            }
        }     

        template<typename sys>
        void attach_system() {
            std::string sys_name = sys::get_name();
            logger->info("System {} has been attatched", sys_name);

            auto system_logger = logger::create_from_name(sys_name);
            attached_systems.push_back(std::make_shared<sys>(*this, system_logger));
        }
    private:
        const std::string name;

        SDL_Window* window_handler;
        SDL_GLContext opengl_context;

        std::vector<std::shared_ptr<engine::system>> attached_systems;

        std::vector<std::shared_ptr<engine::scene>> scenes;
        std::shared_ptr<engine::scene> active_scene;

        std::shared_ptr<spdlog::logger> logger;
    protected:
    };
}