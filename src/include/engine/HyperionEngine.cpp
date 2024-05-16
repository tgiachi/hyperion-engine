#include "HyperionEngine.h"

#include "spdlog/spdlog.h"
#include <SDL.h>

#include "../utils/image_scaler.h"

namespace hyperion::engine {
    HyperionEngine::HyperionEngine(EngineOptions *options) {
        _options = options;
        spdlog::info("Initializing Hyperion Engine");
        this->initializeConsole();
    }

    void HyperionEngine::initializeConsole() {
        spdlog::info("Initializing console");
        auto params = TCOD_ContextParams{};
        params.tcod_version = TCOD_COMPILEDVERSION;
        params.renderer_type = _options->renderer;
        params.vsync = _options->vsync;
        params.sdl_window_flags = _options->resizable ? SDL_WINDOW_RESIZABLE : 0;
        params.window_title = _options->windowTitle;


        auto tilesetPath = std::filesystem::path{_options->dataDirectory} / std::filesystem::path
                           {_options->tilesetName};

        if (_options->tileSetScale > 1.0) {
            spdlog::info("Scaling tileset by {}", _options->tileSetScale);
            auto newScaledFileName = (tilesetPath.c_str() + std::string("_scaled.png")).c_str();
            utils::images::scaleTileset(tilesetPath.c_str(), newScaledFileName,
                                        _options->tileSetScale);

            tilesetPath = newScaledFileName;
        }

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

        tcod::print(*this->_rootConsole, {10, 11}, std::format("delta: {}", this->_deltaTime),
                    TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_CENTER);
    }


    void HyperionEngine::update() {
    }


    void HyperionEngine::run() {
        //SDL_Event event;


        while (this->_running) {
            this->_lastUpdate = this->_currentTick;
            this->_currentTick = SDL_GetPerformanceCounter();
            this->_deltaTime = (this->_currentTick - this->_lastUpdate) * 1000 / SDL_GetPerformanceFrequency();

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
