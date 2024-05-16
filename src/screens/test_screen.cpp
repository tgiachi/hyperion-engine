//
// Created by squid on 5/16/24.
//

#include "test_screen.h"

#include <spdlog/spdlog.h>


namespace hyperion::engine::screen {
    void TestScreen::update(double deltaTime) {
        // random character

        _time += deltaTime;

        if (_time > 1000) {
            // random character
            char rndd = rand() % this->getWidth();

            // rndd to string
            std::string rndd_str = std::to_string(rndd);

            for (int x = 0; x < this->getWidth(); x++) {
                for (int y = 0; y < this->getHeight(); y++) {
                    tcod::print(*this->getConsole()->get(), {x, y}, rndd_str, TCOD_ColorRGB{0xff, 0xff, 0xff},
                                std::nullopt);
                }
            }
            _time = 0;
        }
    }
}
