#pragma once

#include "engine/ecs/components.hh"
#include "engine/system/system.hh"

struct player_component {
    float movement_speed;
};

class player_system : public engine::system {
    SYSTEM_BOILERPLATE(player_system)
public:
    player_system(std::shared_ptr<spdlog::logger> logger);

    void on_update() override;
private:
protected:
};