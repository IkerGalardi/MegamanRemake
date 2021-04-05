#include "physics_system.hh"

namespace engine {
    physics_system::physics_system(std::shared_ptr<spdlog::logger> logger) 
        : system(logger),
          world(b2Vec2{0, -9.8})
    {
    }

    physics_system::~physics_system() {

    }


    b2Body* physics_system::create_box(transform_component transform) {
        // Define the body
        b2BodyDef definition;
        definition.position.Set(transform.position.x, transform.position.y);
        b2Body* res = world.CreateBody(&definition);

        // Set the shape of the body
        b2PolygonShape shape;
        shape.SetAsBox(transform.scale.y / 2, transform.scale.x / 2);
        res->CreateFixture(&shape, 0.0f);

        return res;
    }

    void physics_system::on_update(float dtime) {
        static float acum_dtime = 0;
        acum_dtime += dtime;

        // Just step on fixed time stamps
        if(acum_dtime > 0.033333333f) {
            acum_dtime = 0.0f;
            world.Step(0.033333333f, 1, 1);
        }
    }
}