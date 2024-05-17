#ifndef HYPERIONENGINE_H
#define HYPERIONENGINE_H
#include <SDL.h>


#include "../types/engine_options.h"
#include "../types/contexts.h"
#include "../types/engine_context.h"
#include <libtcod.hpp>

#include "../screen/screen_console.h"

using namespace hyperion::engine::contexts;

namespace hyperion::engine {
    class HyperionEngine {
    private:
        EngineOptions _options;
        EngineContext _engine_context;
        tcod::Context _context;
        tcod::Console *_rootConsole{};

        MousePosition _mousePosition{};
        ScreenSize _screenSize{};
        TilesSize _tilesSize{};

        std::vector<hyperion::engine::screen::ScreenConsole *> _screenConsoles;

        uint64_t _lastUpdate = 0;
        uint64_t _currentTick = 0;
        Uint32 _deltaTime = 0;


        bool _running;

        void initializeConsole();

        void render();

        void update_inputs(const SDL_Event *event);

        void update(const SDL_Event *event);

    public:
        HyperionEngine(EngineOptions &options);

        ~HyperionEngine();

        void run();
    };
}

#endif //HYPERIONENGINE_H
