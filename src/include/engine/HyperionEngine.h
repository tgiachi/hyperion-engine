#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include "../types/engine_options.h"

namespace hyperion::engine {
    class HyperionEngine {
    private:
        EngineOptions *_options;
        tcod::Context _context;
        TCOD_Console *_rootConsole;

        void initializeConsole();

    public:
        HyperionEngine(EngineOptions *options);

        ~HyperionEngine();
    };
}

#endif //HYPERIONENGINE_H
