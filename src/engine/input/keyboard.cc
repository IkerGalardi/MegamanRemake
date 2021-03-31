#include "keyboard.hh"

namespace engine {
    keyboard::keyboard() {
        // Set the keyboard to be blank at the start
        /// TODO: see if this is a problem
        memset(state, false, SDLK_END * sizeof(bool));
        memset(down, false, SDLK_END * sizeof(bool));
        memset(up, false, SDLK_END * sizeof(bool));
    }

    bool keyboard::get_key_state(uint32 keycode) {
        return state[keycode];
    }

    bool keyboard::get_key_down(uint32 keycode) {
        return down[keycode];
    }

    bool keyboard::get_key_up(uint32 keycode) {
        return up[keycode];
    }


    void keyboard::on_key_pressed(uint32 keycode) {
        state[keycode] = true;
        down[keycode] = true;
    }

    void keyboard::on_key_released(uint32 keycode) {
        state[keycode] = false;
        up[keycode] = true;
    }

    void keyboard::on_update() {
        memset(down, false, SDLK_END * sizeof(bool));
        memset(up, false, SDLK_END * sizeof(bool));
    }
}