#include "scene.hh"

#include "components.hh"
#include "engine/logger.hh"

namespace engine {
    scene::scene(const std::string& name, std::function<void(scene&)> func) 
        : bootstrap_function(func),
          scene_name(name)
    {
        logger = logger::create_from_name(name + " scene");
    }

    entt::entity scene::add_entity(const std::string& entity_name) {
        auto entity = registry.create();

        // Add a name to the entity (necesary for all entities)
        auto& tag = registry.emplace<tag_component>(entity);
        tag.name = entity_name;

        // Add a transform component (necesary for all entities)
        auto& transform = registry.emplace<transform_component>(entity);
        transform.position = { 0.f, 0.f, 0.f };
        transform.scale = { 0.f, 0.f };

        logger->info("Created entity: {}", entity_name);

        return entity;
    }

    void scene::remove_entity(entt::entity& entity) {
        registry.destroy(entity);
    }


    void scene::bootstrap_scene() {
        logger->info("Bootstrapping {} scene...", scene_name);

        // Bootstrap the scene
        bootstrap_function(*this);
    }
}