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
        shape.SetAsBox(transform.scale.x / 2, transform.scale.y / 2);
        res->CreateFixture(&shape, 1.0f);

        logger->info("Registered a body");

        return res;
    }

    void physics_system::on_update(float dtime) {
        static float acum_dtime = 0;
        acum_dtime += dtime;

        // Just step on fixed time stamps
        if(acum_dtime > 0.033333333f/2.0f) {
            acum_dtime = 0.0f;
            world.Step(0.033333333f/2.0f, 8, 6);
        }
        auto& registry = get_scene()->get_registry();
        auto view = registry.view<transform_component, rigidbody>();
        for(auto entity : view) {
            auto [transform, quad] = registry.get<transform_component, rigidbody>(entity);
            
            // Update the position of the transform so that picks the 
            // correct position
            const b2Vec2& pos = quad->GetPosition();
            transform.position.x = pos.x;
            transform.position.y = pos.y;
        }
    }
}