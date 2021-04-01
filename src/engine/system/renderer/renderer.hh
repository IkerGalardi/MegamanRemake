#pragma once 

#include <filesystem>

#include <glm/glm.hpp>

#include "engine/system/system.hh"
#include "opengl/gl.hh"

namespace engine {
    class renderer_system : public engine::system {
        SYSTEM_BOILERPLATE(renderer_system)
    public:
        renderer_system(std::shared_ptr<spdlog::logger> logger);
        ~renderer_system() override;

        void on_update(float dtime) override;
        void on_screen_resize(uint32 width, uint32 height) override;
    private:
        gl::vertex_array varray;
        gl::buffer quad;
        gl::buffer indices;
        gl::shader shader;

        glm::mat4 projection_matrix;
    protected:
    };
}