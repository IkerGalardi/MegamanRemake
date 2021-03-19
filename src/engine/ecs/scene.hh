#pragma once

#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

namespace engine {
    class scene {
    public:
        scene(std::shared_ptr<spdlog::logger> logger);

        entt::entity create_entity(const std::string name);

        void destroy_entity(entt::entity entity);

        entt::registry& get_registry() { return registry; }
    private:
        entt::registry registry;

        std::shared_ptr<spdlog::logger> logger;
    protected:
    };
}