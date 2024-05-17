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
        TCOD_ColorRGB _backgroundColor = TCOD_ColorRGB{0, 128, 0};

    public:
        ScreenConsole(int width, int height, int x, int y) : _consoleRect({x, y, width, height}) {
            _console = new tcod::Console{width, height};
        }


        [[nodiscard]] tcod::Console *getConsole() const {
            return _console;
        }


        void update(double deltaTime) override {
        }

        void render(TCOD_Console *console) override {
            if (_visible) {
                for (int x = 0; x < _consoleRect.w; x++) {
                    for (int y = 0; y < _consoleRect.h; y++) {
                        _console->at({x, y}).bg = _backgroundColor;
                    }
                }

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


        [[nodiscard]] int getX() const {
            return _consoleRect.x;
        }

        [[nodiscard]] int getY() const {
            return _consoleRect.y;
        }

        void setX(const int x) {
            _consoleRect.x = x;
        }

        void setY(const int y) {
            _consoleRect.y = y;
        }

        void setBackgroundColor(const TCOD_ColorRGB &backgroundColor) {
            _backgroundColor = backgroundColor;
        }

        [[nodiscard]] TCOD_ColorRGB getBackgroundColor() const {
            return _backgroundColor;
        }
    };
}

#endif //SCREEN_CONSOLE_H
