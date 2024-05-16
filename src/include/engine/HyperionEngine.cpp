#include "HyperionEngine.h"

#include "spdlog/spdlog.h"
#include <SDL.h>

namespace hyperion::engine {
    HyperionEngine::HyperionEngine(EngineOptions *options) {
        _options = options;
        spdlog::info("Initializing Hyperion Engine");

        this->initializeConsole();
    }

    void HyperionEngine::initializeConsole() {
        auto params = TCOD_ContextParams{};
        params.tcod_version = TCOD_COMPILEDVERSION;
        params.renderer_type = _options->renderer;
        params.vsync = _options->vsync;
        params.sdl_window_flags = _options->resizable ? SDL_WINDOW_RESIZABLE : 0;
        params.window_title = _options->windowTitle;

        auto tilesetPath = std::filesystem::path{_options->dataDirectory} / std::filesystem::path
                           {_options->tilesetName};


        auto defaultTileset = tcod::load_tilesheet(tilesetPath, {32, 8}, tcod::CHARMAP_TCOD);


        params.tileset = defaultTileset.get();


        this->_rootConsole = TCOD_console_new(_options->columns, _options->rows);
        params.console = this->_rootConsole;
        this->_context = tcod::Context(params);
        this->_running = true;
    }

    void HyperionEngine::render() {
        tcod::print(*this->_rootConsole, {10, 10}, "Hello world", TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_CENTER);
    }

    void HyperionEngine::update() {
    }

    void HyperionEngine::run() {
        SDL_Event event;

        while (this->_running) {
            this->_rootConsole->clear();
            this->update();
            this->render();
            this->_context.present(*this->_rootConsole);
        }
    }


    HyperionEngine::~HyperionEngine() {
        delete _options;
        delete _rootConsole;
    }
}
