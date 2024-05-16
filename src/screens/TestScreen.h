//
// Created by squid on 5/16/24.
//

#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "../include/screen/screen_console.h"


namespace hyperion::engine::screen {
    class TestScreen : public ScreenConsole {
    public:
        void update(double deltaTime) override;

        TestScreen(int width, int height, int x, int y) : ScreenConsole(width, height, x, y) {
            this->show();
        }
    };
}


#endif //TESTSCREEN_H
