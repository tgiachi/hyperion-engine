#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "screen_console.h"

namespace hyperion::engine::screen {
    class TestScreen : public ScreenConsole {
        double _time = 0;

    public:
        void update(double deltaTime) override;

        TestScreen(int width, int height, int x, int y) : ScreenConsole(width, height, x, y) {
            this->show();


        }
    };
}


#endif //TESTSCREEN_H
