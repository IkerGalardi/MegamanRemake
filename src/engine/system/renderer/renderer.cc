#include "renderer.hh"

#include <iostream>

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "opengl/gl.hh"
#include "engine/ecs/components.hh"

namespace fs = std::filesystem;

const std::string vertex_source = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 transform;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   TexCoord = aTexCoord;\n"
"}\0";

const std::string fragment_source = 
"#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform vec4 tint_color;\n"
"uniform sampler2D text;\n"
"void main()\n"
"{\n"
"   FragColor = texture(text, TexCoord);\n"
"}\0";

namespace engine {
    renderer_system::renderer_system(std::shared_ptr<spdlog::logger> logger)
        : system(logger),
          quad(gl::buffer_type::array_buffer, gl::draw_type::static_draw),
          indices(gl::buffer_type::element_buffer, gl::draw_type::static_draw),
          shader(vertex_source, fragment_source)
    {
        logger->info("Initializing the rendering system");
        gl::debugging_information(true);
        
        // Add buffers to vertex array
        varray.add_buffer(quad);
        varray.add_buffer(indices);
        varray.set_layout({
            { 3, gl::attrib_type::float32 },
            { 2, gl::attrib_type::float32 }
        });

        // Setup the quad buffer
        {
            float vertices[] = 
            {
                -.5f, -.5f, 0.0f, 0.0f, 0.0f,
                 .5f, -.5f, 0.0f, 1.0f, 0.0f,
                 .5f,  .5f, 0.0f, 1.0f, 1.0f,
                -.5f,  .5f, 0.0f, 0.0f, 1.0f,
            };

            unsigned int elements[] =
            {
                0, 1, 2,
                2, 3, 0
            };

            quad.set_data(vertices, sizeof(vertices));
            indices.set_data(elements, sizeof(elements));
        }

        gl::set_clear_color({1, 1, 0, 1});

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        logger->info("All buffers sent to the GPU, prepared for rendering...");
    }

    renderer_system::~renderer_system() {

    }

    void renderer_system::on_update() {
        gl::clear(GL_COLOR_BUFFER_BIT);

        // Calculate the view transformation matrix and send it to the shader
        auto camera_position = glm::vec3{get_scene()->camera_position, 0.0f};
        auto camera_target = camera_position + glm::vec3{0.0f, 0.0f, -1.0f};
        glm::mat4 view_matrix = glm::lookAt(camera_position, 
                                            camera_target, 
                                            glm::vec3{0.0f, 1.0f, 0.0f});
        shader.set_matrix("view", view_matrix);

        // For every entity with transform and sprite components, render them
        auto& registry = get_scene()->get_registry();
        auto view = registry.view<transform_component, sprite_component>();
        for(auto entity : view) {
            auto [transform, sprite] = view.get<transform_component, sprite_component>(entity);

            // Add the transform as an uniform from the shader. This transform is constructed
            // by multiplying the translation matrix with the scale matrix.
            glm::mat4 trans_matrix = glm::translate(glm::mat4(1.f), glm::vec3(transform.position, 0.0f)) * 
                                     glm::scale(glm::mat4(1.f), glm::vec3(transform.scale, 0.0f));
            shader.set_matrix("transform", trans_matrix);

            // Set the color tint
            shader.set_vector("tint_color", sprite.color);

            // Bind the texture and use it in the shader
            sprite.texture.bind_to_slot(0);
            shader.set_int("text", 0);
            
            // Draw the quad
            gl::draw(shader, varray, 6);
        }
    }

    void renderer_system::on_screen_resize(uint32 width, uint32 height) {
        // Update the opengl viewport to take the whole screen, instead of
        // just the previous region
        glViewport(0, 0, width, height);
        
        // Create the orthographic projection matrix so that the image does
        // not stretch
        float aspect_ration = static_cast<float>(width) / static_cast<float>(height);
        projection_matrix = glm::ortho(-aspect_ration, aspect_ration, -1.0f, 1.0f);
        shader.set_matrix("projection", projection_matrix);
    }
}