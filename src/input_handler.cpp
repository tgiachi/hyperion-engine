//
// Created by squid on 5/16/24.
//

#include "include/engine/input_handler.h"

#include <spdlog/spdlog.h>


namespace hyperion::engine::services {
    void InputHandler::subscribeKeystroke(std::string keystroke, const InputCallback &callback) {
        std::istringstream keystrokeStream(keystroke);
        auto *tokens = new std::vector<std::string>;

        while (std::getline(keystrokeStream, keystroke, '+')) {
            // to lower
            std::transform(keystroke.begin(), keystroke.end(), keystroke.begin(), ::tolower);

            tokens->push_back(keystroke);
        }

        SDL_Keycode key = SDLK_UNKNOWN;

        for (auto &token: *tokens) {
            if (token == "ctrl") {
                key = key | KMOD_CTRL;
            } else if (token == "alt") {
                key = key | KMOD_ALT;
            } else if (token == "shift") {
                key = key | KMOD_SHIFT;
            } else {
                key = key | SDL_GetKeyFromName(token.c_str());
            }
        }

        spdlog::info("Subscribing to keystroke: {}", key);

        keys[key].push_back(callback);

        delete tokens;
    }

    void InputHandler::update(const SDL_Event &event) {
        if (event.type == SDL_KEYDOWN) {
            _keysPressed.push_back(event.key.keysym.sym);
        }

        if (event.type == SDL_KEYUP) {
            std::erase(this->_keysPressed, event.key.keysym.sym);
        }

        SDL_Keycode keycode = SDLK_UNKNOWN;
        for (auto &pressed: this->_keysPressed) {
            if (pressed == SDLK_LCTRL || pressed == SDLK_RCTRL) {
                keycode = keycode | KMOD_CTRL;
                continue;
            }

            if (pressed == SDLK_LALT || pressed == SDLK_RALT) {
                keycode = keycode | KMOD_ALT;
                continue;
            }

            if (pressed == SDLK_LSHIFT || pressed == SDLK_RSHIFT) {
                keycode = keycode | KMOD_SHIFT;
                continue;
            }

            keycode = keycode | pressed;
        }


        if (keys.contains(keycode)) {
            for (auto &callback: keys[keycode]) {
                callback(keycode, SDL_GetKeyName(keycode));
                _keysPressed.clear();
            }
        }
    }
}
