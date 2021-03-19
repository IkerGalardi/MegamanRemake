#include "renderer.hh"

#include <iostream>

#include <entt/entt.hpp>

#include "opengl/gl.hh"
#include "engine/ecs/components.hh"

namespace fs = std::filesystem;

const std::string vertex_source = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   TexCoord = aTexCoord;\n"
"}\0";

const std::string fragment_source = 
"#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(TexCoord ,0.0f, 1.0f);\n"
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

        logger->info("All buffers sent to the GPU, prepared for rendering...");
    }

    renderer_system::~renderer_system() {

    }

    void renderer_system::on_update() {
        gl::clear(GL_COLOR_BUFFER_BIT);
        logger->info("Color cleared");
        
        auto& registry = get_scene()->get_registry();
        auto view = registry.view<transform_component, sprite_component>();
        for(auto entity : view) {
            logger->info("Drawing entity {}", entity);
            auto [transform, sprite] = view.get<transform_component, sprite_component>(entity);

            // Create transform of object
            
            // Add the uniform of position

            // Draw the quad
        }
    }
}