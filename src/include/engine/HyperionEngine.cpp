#include "HyperionEngine.h"

#include "spdlog/spdlog.h"
#include <SDL.h>

namespace hyperion::engine {
    HyperionEngine::HyperionEngine(EngineOptions *options) {
        _options = options;
    }

    void HyperionEngine::initializeConsole() {
        auto params = TCOD_ContextParams{};
        params.tcod_version = TCOD_COMPILEDVERSION;
        params.renderer_type = _options->renderer;
        params.vsync = _options->vsync;
        params.sdl_window_flags = _options->resizable ? SDL_WINDOW_RESIZABLE : 0;
        params.window_title = _options->windowTitle;
        this->_rootConsole = TCOD_console_new(_options->columns, _options->rows);
        this->_context = tcod::Context(params);;
    }


    HyperionEngine::~HyperionEngine() {
        delete _options;
    }
}
