#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include <SDL.h>


#include "../types/engine_options.h"
#include "../types/contexts.h"
#include "../types/engine_context.h"
#include <libtcod.hpp>

using namespace hyperion::engine::contexts;

namespace hyperion::engine {
    namespace screen {
        class ScreenConsole;
    }

    class HyperionEngine {
    private:
        EngineOptions *_options;
        EngineContext *_engine_context;
        tcod::Context _context;
        tcod::Console *_rootConsole;

        MousePosition *_mousePosition;
        ScreenSize *_screenSize;
        TilesSize *_tilesSize;

        std::vector<screen::ScreenConsole *> _screenConsoles;

        Uint64 _lastUpdate = 0;
        Uint64 _currentTick = 0;
        double _deltaTime = 0;



        bool _running;

        void initializeConsole();

        void render();

        void update_inputs(const SDL_Event *event) const;

        void update(const SDL_Event *event);

    public:
        HyperionEngine(EngineOptions *options);

        ~HyperionEngine();

        void run();
    };
}

#endif //HYPERIONENGINE_H
