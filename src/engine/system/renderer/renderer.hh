#pragma once 

#include <filesystem>

#include "engine/system/system.hh"
#include "opengl/gl.hh"

namespace engine {
    class renderer_system : public engine::system {
        SYSTEM_BOILERPLATE(renderer_system)
    public:
        renderer_system(const engine::application& app, std::shared_ptr<spdlog::logger> logger);
        ~renderer_system() override;

        void on_update() override;
    private:
        gl::vertex_array varray;
        gl::buffer quad;
        gl::buffer indices;

        gl::shader shader;
    protected:
    };
}