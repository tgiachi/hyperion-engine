#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include <SDL.h>


#include "../types/engine_options.h"
#include "../types/contexts.h"
#include "../types/engine_context.h"


using namespace hyperion::engine::contexts;

namespace hyperion::engine {
    class HyperionEngine {
    private:
        EngineOptions *_options;
        EngineContext *_engine_context;
        tcod::Context _context;
        TCOD_Console *_rootConsole;

        MousePosition *_mousePosition;
        ScreenSize *_screenSize;
        TilesSize *_tilesSize;

        Uint64 _lastUpdate = 0;
        Uint64 _currentTick = 0;
        double _deltaTime = 0;

        std::vector<SDL_Keycode> _keysPressed;

        bool _running;

        void initializeConsole();

        void render();

        void update_inputs(SDL_Event *event);

        void update(SDL_Event *event);

    public:
        HyperionEngine(EngineOptions *options);

        ~HyperionEngine();

        void run();
    };
}

#endif //HYPERIONENGINE_H
