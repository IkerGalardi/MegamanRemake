#include "player_system.hh"

#include "engine/application.hh"
#include "engine/system/physics/physics_system.hh"

player_system::player_system(std::shared_ptr<spdlog::logger> logger) 
    : engine::system(logger)
{
}

void player_system::on_update(float dtime) {
    auto& registry = get_scene()->get_registry();
    auto view = registry.view<engine::transform_component, player_component>();
    for(auto entity : view) {
        auto [transform, rigid, player] = registry.get<engine::transform_component, 
                                                       engine::rigidbody, 
                                                       player_component>(entity);

        b2Vec2 movement{0.0f, 0.0f};
        float scale = transform.scale.x;
        if(engine::application::get().keyboard().key_state(SDLK_a)) {
            // Move the player
            movement.x = -player.movement_speed * dtime;
            
            // Flip the player if it needs to be fliped
            if(scale > 0) {
                transform.scale.x = -scale;
            }
            rigid->ApplyForceToCenter(20 * movement, true);
        } 
        if(engine::application::get().keyboard().key_state(SDLK_d)) {
            // Move the player
            movement.x = player.movement_speed * dtime;

            // Flip the player if it needs to be fliped
            if(scale < 0) {
                transform.scale.x = -scale;
            }
            rigid->ApplyForceToCenter(20 * movement, true);
        }
        
        if(engine::application::get().keyboard().key_state(SDLK_SPACE)) {
            rigid->ApplyLinearImpulseToCenter(b2Vec2{0.0, 0.0003}, true);
        } else {
            rigid->ApplyLinearImpulseToCenter(b2Vec2_zero, true);
        }
    }
}