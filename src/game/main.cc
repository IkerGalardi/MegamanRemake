#include "engine/application.hh"
#include "engine/system/renderer/renderer.hh"
#include "engine/ecs/components.hh"

int main(int argc, char** argv) {
    // Adding all systems
    engine::application::get().attach_system<engine::renderer_system>();

    // Setup all scenes
    engine::application::get().attach_scene([](engine::scene& scene){
        scene.camera_position = {0.0f, 0.0f};

        // Create An entity with the name 'square'
        auto entity = scene.create_entity("square");

        // Add a sprite component so it can be rendered
        auto& sprite = scene.get_registry().emplace<engine::sprite_component>(entity);
        sprite.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        sprite.texture = gl::texture(std::filesystem::path("assets/sprites/test.png"));

        // Move the square a bit to the right and stretch it
        auto& transform = scene.get_registry().get<engine::transform_component>(entity);
        transform.position = glm::vec2(0.2f, 0.0f);
        transform.scale = glm::vec2(1.f, 1.f);
    }, "test_scene");

    // Start the game
    engine::application::get().start();
}