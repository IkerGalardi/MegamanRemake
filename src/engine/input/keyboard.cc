#include "keyboard.hh"

namespace engine {
    keyboard::keyboard() {
        // Set the keyboard to be blank at the start
        /// TODO: see if this is a problem
        memset(state, false, SDLK_END * sizeof(bool));
        memset(down, false, SDLK_END * sizeof(bool));
        memset(up, false, SDLK_END * sizeof(bool));
    }

    bool keyboard::key_state(uint32 keycode) {
        return state[keycode];
    }

    void keyboard::on_key_pressed(uint32 keycode) {
        state[keycode] = true;
    }

    void keyboard::on_key_released(uint32 keycode) {
        state[keycode] = false;
    }

    void keyboard::on_update() {
    }
}