#include "player_system.hh"

#include "engine/application.hh"

player_system::player_system(std::shared_ptr<spdlog::logger> logger) 
    : engine::system(logger)
{
}

void player_system::on_update() {
    auto& registry = get_scene()->get_registry();
    auto view = registry.view<engine::transform_component, player_component>();
    for(auto entity : view) {
        auto [transform, player] = registry.get<engine::transform_component, player_component>(entity);

        if(engine::application::get().keyboard().key_state(SDLK_a)) {
            transform.position.x -= player.movement_speed * 0.001f;
        } else if(engine::application::get().keyboard().key_state(SDLK_d)) {
            transform.position.x += player.movement_speed * 0.001f;
        }
    }
}