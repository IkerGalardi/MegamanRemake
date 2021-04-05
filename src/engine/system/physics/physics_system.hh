#pragma once

#include <box2d/box2d.h>

#include "engine/ecs/components.hh"
#include "engine/system/system.hh"


namespace engine {
    typedef b2Body* rigidbody;
    
    class physics_system : public engine::system {
        SYSTEM_BOILERPLATE(physics_system)
    public:
        physics_system(std::shared_ptr<spdlog::logger> logger);
        ~physics_system();

        b2Body* create_box(transform_component transform);

        void on_update(float dtime) override;
    private:
        b2World world;
    protected:
    };
}