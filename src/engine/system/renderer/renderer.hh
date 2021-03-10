#pragma once 

#include <filesystem>

#include "engine/system/system.hh"
#include "opengl/gl.hh"

namespace engine {
    class renderer_system : public engine::system {
    public:
        renderer_system(const engine::application& app);
        ~renderer_system() override;

        virtual void on_update() override;
        virtual void on_destroy() override;
    private:
        gl::vertex_array varray;
        gl::buffer quad;
        gl::buffer indices;

        gl::shader shader;
    protected:
    };
}