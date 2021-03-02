#include "renderer.hh"

namespace fs = std::filesystem;

namespace engine {
    renderer_system::renderer_system(const engine::application& app)
        : system(app),
          quad(gl::buffer_type::array_buffer, gl::draw_type::static_draw),
          indices(gl::buffer_type::element_buffer, gl::draw_type::static_draw),
          shader(fs::path("shaders/basicvertex.vert"), fs::path("shaders/color.frag"))
    {
        // Add buffers to vertex array
        varray.add_buffer(quad);
        varray.add_buffer(indices);
        varray.set_layout({
            { 3, gl::attrib_type::float32 },
            { 2, gl::attrib_type::float32 }
        });

        gl::set_clear_color({1, 1, 1, 1});
    }

    renderer_system::~renderer_system() {

    }

    void renderer_system::on_update() {
        gl::clear(GL_COLOR_BUFFER_BIT);
    }

    void renderer_system::on_destroy() {

    }
}