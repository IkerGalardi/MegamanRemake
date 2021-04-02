#include "player_system.hh"

#include "engine/application.hh"

player_system::player_system(std::shared_ptr<spdlog::logger> logger) 
    : engine::system(logger)
{
}

void player_system::on_update(float dtime) {
    auto& registry = get_scene()->get_registry();
    auto view = registry.view<engine::transform_component, player_component>();
    for(auto entity : view) {
        auto [transform, player] = registry.get<engine::transform_component, player_component>(entity);
        float scale = transform.scale.x;
        if(engine::application::get().keyboard().key_state(SDLK_a)) {
            // Move the player
            transform.position.x -= player.movement_speed * dtime;
            
            // Flip the player if it needs to be fliped
            if(scale > 0) {
                transform.scale.x = -scale;
            }
        } 
        if(engine::application::get().keyboard().key_state(SDLK_d)) {
            // Move the player
            transform.position.x += player.movement_speed * dtime;

            // Flip the player if it needs to be fliped
            if(scale < 0) {
                transform.scale.x = -scale;
            }
        }
    }
}