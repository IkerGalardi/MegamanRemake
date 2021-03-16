#include "engine/application.hh"
#include "engine/system/renderer/renderer.hh"

int main(int argc, char** argv) {
    // Adding all systems
    engine::application::get().attach_system<engine::renderer_system>();

    // Setup all scenes
    engine::application::get().start();
}