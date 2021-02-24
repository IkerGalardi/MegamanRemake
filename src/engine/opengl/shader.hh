#pragma once 

#include <string>
#include <filesystem>

#include "glm/glm.hpp"

#include "common.hh"

/// TODO: 
///    - Uniform location cacheing????

namespace gl {
    class buffer;

    class shader {
        friend void draw(const gl::shader& shader, const gl::buffer& buffer);
    public:
        shader() = default;
        shader(const std::string& vs, const std::string& fs);
        shader(const std::filesystem::path& vs, const std::filesystem::path& fs);
        ~shader();

        void set_vector(const std::string& name, glm::vec2 vector);
        void set_vector(const std::string& name, glm::vec3 vector);
        void set_vector(const std::string& name, glm::vec4 vector);
    private:
        bool is_initialized = false;

        uint32 id;
    protected:
    };
}