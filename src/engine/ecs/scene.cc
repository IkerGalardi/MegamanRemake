#include "scene.hh"

#include "components.hh"

namespace engine {
    scene::scene(std::shared_ptr<spdlog::logger> logger) 
        : logger(logger),
          camera_position(0.0f, 0.0f)
    {
    }

    entt::entity scene::create_entity(const std::string name) {
        auto entity = this->registry.create();

        // Add a tag component to the entity. All entities should have one
        auto& tag_c = registry.emplace<tag_component>(entity);
        tag_c.name = name;
        tag_c.layer = 0;

        // Add transform component to the entity. All entities should have one
        auto& transform = registry.emplace<transform_component>(entity);
        transform.position = glm::vec2{ 0.0f, 0.0f };
        transform.scale = glm::vec2{ 1.0f, 1.0f };

        return entity;
    }


    void scene::destroy_entity(entt::entity entity) {
        registry.destroy(entity);
    }
}