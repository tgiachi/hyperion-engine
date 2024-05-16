#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include <SDL_stdinc.h>

#include "../types/engine_options.h"

namespace hyperion::engine {
    class HyperionEngine {
    private:
        EngineOptions *_options;
        tcod::Context _context;
        TCOD_Console *_rootConsole;
        Uint64 _lastUpdate = 0;
        Uint64 _currentTick = 0;
        double _deltaTime = 0;

        bool _running;

        void initializeConsole();

        void render();

        void update();

    public:
        HyperionEngine(EngineOptions *options);

        ~HyperionEngine();

        void run();
    };
}

#endif //HYPERIONENGINE_H
