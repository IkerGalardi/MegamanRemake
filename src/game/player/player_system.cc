#include "player_system.hh"

#include "engine/application.hh"
#include "engine/system/physics/physics_system.hh"

player_system::player_system(std::shared_ptr<spdlog::logger> logger) 
    : engine::system(logger)
{
}

void player_system::on_update(float dtime) {
    static float acum = 0.0f;
    acum += dtime;

    if(acum > 0.033333333f/2.0f) {
        acum = 0.0f;

        auto& registry = get_scene()->get_registry();
        auto view = registry.view<engine::transform_component, player_component>();
        for(auto entity : view) {
            auto [transform, rigid, player] = registry.get<engine::transform_component, 
                                                           engine::rigidbody, 
                                                           player_component>(entity);

            b2Vec2 movement{0.0f, 0.0f};
            float scale = transform.scale.x;
            bool a_press = engine::application::get().keyboard().key_state(SDLK_a);
            bool b_press = engine::application::get().keyboard().key_state(SDLK_d);
            if(a_press) {
                // Move the player
                movement.x = -player.movement_speed;

                // Flip the player if it needs to be fliped
                if(scale > 0) {
                    transform.scale.x = -scale;
                }
                
                rigid->SetLinearVelocity(movement);
            } 
            if(b_press) {
                // Move the player
                movement.x = player.movement_speed;

                // Flip the player if it needs to be fliped
                if(scale < 0) {
                    transform.scale.x = -scale;
                }
                
                rigid->SetLinearVelocity(movement);
            }

            if((!a_press && !b_press) || (a_press && b_press)) {
                rigid->SetLinearVelocity(b2Vec2_zero);
                transform.scale.x = scale;
            }

            //if(engine::application::get().keyboard().key_state(SDLK_SPACE)) {
            //    rigid->ApplyLinearImpulseToCenter(b2Vec2{0.0, .05f}, true);
            //} else {
            //    rigid->ApplyLinearImpulseToCenter(b2Vec2_zero, true);
            //}
        }
    }
}