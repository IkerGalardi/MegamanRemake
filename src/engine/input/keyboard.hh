#pragma once

#include <SDL2/SDL_keycode.h>

#include "common.hh"

namespace engine {
    // Fordward declaration
    class application;

    class keyboard {
        friend class application;
    public:
        bool key_state(uint32 keycode);
    private:
        void on_key_pressed(uint32 keycode);
        void on_key_released(uint32 keycode);
        void on_update();

        keyboard();
        ~keyboard() = default;

        bool state[SDLK_END];
        bool down[SDLK_END];
        bool up[SDLK_END];
    protected:
    };
}