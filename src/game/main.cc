#include "engine/application.hh"
#include "engine/system/renderer/renderer.hh"
#include "engine/ecs/components.hh"

int main(int argc, char** argv) {
    // Adding all systems
    engine::application::get().attach_system<engine::renderer_system>();

    // Setup all scenes
    engine::application::get().attach_scene([](engine::scene& scene){
        auto entity = scene.create_entity("square");
        engine::sprite_component& sprite = scene.get_registry().emplace<engine::sprite_component>(entity);
        sprite.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

        auto& transform = scene.get_registry().get<engine::transform_component>(entity);
        transform.position = glm::vec2(1.0f, 0.0f);
    }, "test_scene");

    // Start the game
    engine::application::get().start();
}