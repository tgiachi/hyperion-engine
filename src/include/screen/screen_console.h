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
        float _alpha = 1.0f;

    public:
        ScreenConsole(int width, int height, int x, int y) : _consoleRect({x, y, width, height}) {
            _console = new tcod::Console{width, height};
        }

        ~ScreenConsole();

        [[nodiscard]] tcod::Console *getConsole() const {
            return _console;
        }


        void update(double deltaTime) override {
        }

        void render(TCOD_Console *console) override {
            if (_visible) {
                tcod::blit(*console, *_console->get(), {_consoleRect.x, _consoleRect.y}, {0, 0, 0, 0}, _alpha, _alpha);
            }
        }

        void show() {
            _visible = true;
        }

        void hide() {
            _visible = false;
        }

        [[nodiscard]] float getAlpha() const {
            return _alpha;
        }

        void setAlpha(float alpha) {
            _alpha = alpha;
        }

        [[nodiscard]] int getWidth() const {
            return _consoleRect.w;
        }

        [[nodiscard]] int getHeight() const {
            return _consoleRect.h;
        }
    };
}

#endif //SCREEN_CONSOLE_H
