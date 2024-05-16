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
        // parse string to SDL_Keycode and add to enum
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

        spdlog::debug("Subscribing to keystroke: {}", key);

        keys[key].push_back(callback);

        delete tokens;
    }
}
