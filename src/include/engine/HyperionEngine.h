#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include <SDL_stdinc.h>

#include "../types/engine_options.h"
#include "../types/mouse_position.h"

namespace hyperion::engine {
    class HyperionEngine {
    private:
        EngineOptions *_options;
        tcod::Context _context;
        TCOD_Console *_rootConsole;
        MousePosition *_mousePosition;

        Uint64 _lastUpdate = 0;
        Uint64 _currentTick = 0;
        double _deltaTime = 0;

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
