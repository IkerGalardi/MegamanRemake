#pragma once

#include <entt/entt.hpp>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

namespace engine {
    class scene {
    public:
        scene(std::shared_ptr<spdlog::logger> logger);

        entt::entity create_entity(const std::string name);

        void destroy_entity(entt::entity entity);

        entt::registry& get_registry() { return registry; }

        glm::vec2 camera_position;
    private:
        entt::registry registry;

        std::shared_ptr<spdlog::logger> logger;
    protected:
    };
}