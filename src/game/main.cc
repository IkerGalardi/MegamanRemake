#include "engine/application.hh"
#include "engine/system/renderer.hh"

int main(int argc, char** argv) {
    engine::application app("Megaman Remake");

    // Adding all systems
    app.attach_system<engine::renderer_system>();

    app.start();
}