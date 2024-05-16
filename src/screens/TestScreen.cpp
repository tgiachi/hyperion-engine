//
// Created by squid on 5/16/24.
//

#include "TestScreen.h"

#include <spdlog/spdlog.h>


namespace hyperion::engine::screen {
    void TestScreen::update(double deltaTime) {
        tcod::print(*this->getConsole()->get(), {1, 1}, "Hello World", TCOD_ColorRGB{0xff, 0xff, 0xff}, std::nullopt);
    }
}
