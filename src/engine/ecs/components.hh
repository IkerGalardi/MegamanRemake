#pragma once 

#include <string>
#include <glm/glm.hpp>

#include "common.hh"

namespace engine {
    struct tag_component {
        std::string name;
        uint32 layer;
    };

    struct transform_component {
        glm::vec2 position;
        glm::vec2 scale;
    };

    struct sprite_component {
        glm::vec4 color;
    };
}