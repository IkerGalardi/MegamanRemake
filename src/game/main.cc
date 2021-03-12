#include "engine/application.hh"
#include "engine/system/renderer/renderer.hh"

int main(int argc, char** argv) {
    engine::application app("Megaman Remake");

    // Adding all systems
    app.attach_system<engine::renderer_system>();

    // Setup all scenes

    app.start();
}