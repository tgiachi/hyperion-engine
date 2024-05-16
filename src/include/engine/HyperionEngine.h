#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include "../types/engine_options.h"

namespace hyperion::engine {
    class HyperionEngine {
    private:
        EngineOptions *_options;
        tcod::Context _context;
        TCOD_Console *_rootConsole;

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
