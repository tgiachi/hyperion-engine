#ifndef SCREEN_CONSOLE_H
#define SCREEN_CONSOLE_H
#include <SDL.h>


#include "../entities/rendable_entity.h"
#include "../entities/updatable_entity.h"


namespace hyperion::engine::screen {
    class ScreenConsole : public entities::RendableEntity, public entities::UpdatableEntity {
    private:
        SDL_Rect _consoleRect;
        tcod::Console *_console;
        bool _visible = false;

    public:
        ScreenConsole(int width, int height, int x, int y) : _consoleRect({x, y, width, height}) {
            _console = new tcod::Console{width, height};
        }

        ~ScreenConsole();

        void render(TCOD_Console *console) override {
            if (_visible) {
                tcod::blit(*console, *_console, {_consoleRect.x, _consoleRect.y}, {0, 0, 0, 0}, 1.0f, 1.0f);
            }
        }

        void show() {
            _visible = true;
        }

        void hide() {
            _visible = false;
        }
    };
}

#endif //SCREEN_CONSOLE_H
