#include "shader.hh"

#include <fstream>

#include <GL/glew.h>

namespace gl {
        shader::shader(const std::string& vs, const std::string& fs) {
            const char* vertex_source = vs.c_str();
            const char* fragment_source = fs.c_str();

            uint32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
            glCompileShader(vertex_shader);

            uint32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
            glCompileShader(fragment_shader);

            id = glCreateProgram();
            glAttachShader(id, vertex_shader);
            glAttachShader(id, fragment_shader);
            glLinkProgram(id);
            glValidateProgram(id);

            is_initialized = true;
        }

        shader::shader(const std::filesystem::path& vs, const std::filesystem::path& fs) {
            std::ifstream vertex_file(vs);
            std::stringstream vs_stream;
            vs_stream << vertex_file.rdbuf();

            std::ifstream fragment_file(vs);
            std::stringstream fs_stream;
            fs_stream << fragment_file.rdbuf();

            shader(vs_stream.str(), fs_stream.str());
        }

        shader::~shader() {
            if(is_initialized)
                glDeleteProgram(id);
        }

        void shader::set_vector(const std::string& name, glm::vec2 vector) {
            int loc = glGetUniformLocation(id, name.c_str());
            glUniform2f(loc, vector.x, vector.y);
        }

        void shader::set_vector(const std::string& name, glm::vec3 vector) {
            int loc = glGetUniformLocation(id, name.c_str());
            glUniform3f(loc, vector.x, vector.y, vector.z);
        }

        void shader::set_vector(const std::string& name, glm::vec4 vector) {
            int loc = glGetUniformLocation(id, name.c_str());
            glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
        } 
}