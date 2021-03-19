#pragma once

#include <string>

#include <spdlog/spdlog.h>

#include "engine/ecs/scene.hh"

#define SYSTEM_BOILERPLATE(sys) public: static std::string get_name() { return  #sys; }

namespace engine {
    class application;

    class system {
    public:
        system(std::shared_ptr<spdlog::logger> logger);
        virtual ~system() = default;

        virtual void on_update() {}
    private:
    protected:
        std::shared_ptr<engine::scene> get_scene();
        std::shared_ptr<spdlog::logger> logger;
    };
}