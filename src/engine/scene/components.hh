#pragma once

#include <string>

#include <glm/glm.hpp>

namespace engine {
    struct tag_component {
        std::string name;
    };

    struct transform_component {
        glm::vec3 position;
        glm::vec2 scale;
    };
}