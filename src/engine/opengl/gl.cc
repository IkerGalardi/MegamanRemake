#include "gl.hh"

namespace gl {
    void set_clear_color(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void clear(uint32 clear_mask) {
        glClear(clear_mask);
    }

    void draw(const gl::shader& shader, const gl::buffer& buffer) {
        glBindVertexArray(0);

        glUseProgram(shader.id);
        glBindBuffer(static_cast<uint32>(buffer.btype), buffer.id);
        glDrawBuffer(GL_BACK);
    }
}