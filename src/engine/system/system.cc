#include "system.hh"

#include "engine/application.hh"

namespace engine {
    system::system(std::shared_ptr<spdlog::logger> logger) 
    {
        this->logger = logger;
    }


    std::shared_ptr<engine::scene> system::get_scene() {
        return application::get().active_scene;
    }
}