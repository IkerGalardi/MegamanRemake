#include <iostream>

#include <glm/glm.hpp>

#include "engine/application.hh"
#include "engine/system/system.hh"
#include "engine/system/renderer/renderer.hh"
#include "engine/system/physics/physics_system.hh"
#include "engine/ecs/components.hh"
#include "engine/logger.hh"

#include "game_components.hh"
#include "player/player_system.hh"

class auto_movement_system : public engine::system {
    SYSTEM_BOILERPLATE(auto_movement_system)
public:
    auto_movement_system(std::shared_ptr<spdlog::logger> logger) 
        : engine::system(logger)
    {
    }

    void on_update(float dtime) override {
        auto& registry = get_scene()->get_registry();
        auto view = registry.view<engine::transform_component, engine::tag_component>();
        for(auto entity : view) {
            auto [transform, tag] = registry.get<engine::transform_component, engine::tag_component>(entity);
            //logger->trace("entity {} with position ({}, {})", tag.name, transform.position.x, transform.position.y);
        }
    }
private:
protected:
};

int main(int argc, char** argv) {
    // Adding all systems
    engine::application::get().attach_system<engine::renderer_system>();
    auto physics = engine::application::get().attach_system<engine::physics_system>();
    engine::application::get().attach_system<auto_movement_system>();
    engine::application::get().attach_system<player_system>();

    // Setup all scenes
    engine::application::get().attach_scene([&](engine::scene& scene){
        scene.camera_position = { 0.0f, 0.0f };

        auto player = scene.create_entity("player");
        auto& transform = scene.get_registry().get<engine::transform_component>(player);
        transform.position = { 0.0f, 0.0f };
        transform.scale = { 0.23f, 0.25f };
        auto& sprite3 = scene.get_registry().emplace<engine::sprite_component>(player);
        sprite3.texture = std::make_shared<gl::texture>("assets/sprites/player.png");
        auto& player3 = scene.get_registry().emplace<player_component>(player);
        player3.movement_speed = 1.0f;
        auto quadcol = scene.get_registry().emplace<engine::rigidbody>(player, physics->create_box(transform));
        quadcol->SetType(b2_dynamicBody);

        auto floor = scene.create_entity("floor");
        auto& fl_transform = scene.get_registry().get<engine::transform_component>(floor);
        fl_transform.position = { 0.0f, -1.0f };
        fl_transform.scale = { 5.0f, 1.0f };
        auto& fl_sprite = scene.get_registry().emplace<engine::sprite_component>(floor);
        fl_sprite.texture = std::make_shared<gl::texture>("assets/sprites/test.png");
        auto floorcol = scene.get_registry().emplace<engine::rigidbody>(floor, physics->create_box(fl_transform));
        floorcol->SetType(b2_staticBody);

    }, "test_scene");

    // Start the game
    engine::application::get().start();
}