//
// Created by squid on 5/16/24.
//

#include "InputHandler.h"

#include <spdlog/spdlog.h>


namespace hyperion::engine::services {
    void InputHandler::subscribeKeystroke(std::string keystroke, InputCallback callback) {
        std::istringstream keystrokeStream(keystroke);
        auto *tokens = new std::vector<std::string>;

        while (std::getline(keystrokeStream, keystroke, '+')) {
            tokens->push_back(keystroke);
        }

        SDL_Keycode key = SDLK_UNKNOWN;

        for (auto &token: *tokens) {
            if (token == "CTRL") {
                key = key | KMOD_CTRL;
            } else if (token == "ALT") {
                key = key | KMOD_ALT;
            } else if (token == "SHIFT") {
                key = key | KMOD_SHIFT;
            } else {
                key = key | SDL_GetKeyFromName(token.c_str());
            }
        }

        spdlog::info("Subscribing to keystroke: {}", key);

        keys[key].push_back(callback);

        delete tokens;
    }

    void InputHandler::update(SDL_Event *event) {
        if (event->type == SDL_KEYDOWN) {
            this->_keysPressed.push_back(event->key.keysym.sym);
        }

        if (event->type == SDL_KEYUP) {
            this->_keysPressed.erase(
                std::remove(this->_keysPressed.begin(), this->_keysPressed.end(), event->key.keysym.sym),
                this->_keysPressed.end());
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


        if (keys.find(keycode) != keys.end()) {
            for (auto &callback: keys[keycode]) {
                callback(keycode, SDL_GetKeyName(keycode));
            }
        }
    }
}
