#include <iostream>

#include <glm/glm.hpp>

#include "engine/application.hh"
#include "engine/system/system.hh"
#include "engine/system/renderer/renderer.hh"
#include "engine/ecs/components.hh"
#include "engine/logger.hh"

class movement_system : public engine::system {
    SYSTEM_BOILERPLATE(movement_system)
public:
    movement_system(std::shared_ptr<spdlog::logger> logger) 
        : engine::system(logger),
          t(0.0f)
    {
    }

    void on_update() override {
        auto& registry = get_scene()->get_registry();
        auto view = registry.view<engine::transform_component>();
        for(auto entity : view) {
            auto& transform = registry.get<engine::transform_component>(entity);
            transform.position += glm::vec2{0.0f, std::sin(t) * 0.01f};
        }

        t += 0.1f;
    }
private:
    float t;
protected:
};

int main(int argc, char** argv) {
    // Adding all systems
    engine::application::get().attach_system<engine::renderer_system>();
    engine::application::get().attach_system<movement_system>();

    // Setup all scenes
    engine::application::get().attach_scene([](engine::scene& scene){
        scene.camera_position = {0.0f, 0.0f};

        auto entity = scene.create_entity("square");
        auto& sprite = scene.get_registry().emplace<engine::sprite_component>(entity);
        sprite.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        sprite.texture = std::make_shared<gl::texture>(std::filesystem::path("assets/sprites/test.png"));
        auto& transform = scene.get_registry().get<engine::transform_component>(entity);
        transform.position = glm::vec2(0.2f, 0.0f);
        transform.scale = glm::vec2(.5f, .5f);
        
        auto entity2 = scene.create_entity("another");
        auto& sprite2 = scene.get_registry().emplace<engine::sprite_component>(entity2);
        sprite2.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        sprite2.texture = std::make_shared<gl::texture>(std::filesystem::path("assets/sprites/test2.png"));
        auto& transform2 = scene.get_registry().get<engine::transform_component>(entity2);
        transform2.position = glm::vec2(-.2f, 0.0f);
        transform2.scale = glm::vec2(.5f, .5f);
    }, "test_scene");

    // Start the game
    engine::application::get().start();
}