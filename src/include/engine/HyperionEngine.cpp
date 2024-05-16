#include "HyperionEngine.h"

#include "spdlog/spdlog.h"
#include <SDL.h>

#include "../utils/image_scaler.h"

namespace hyperion::engine {
    HyperionEngine::HyperionEngine(EngineOptions *options) {
        _options = options;
        _mousePosition = new MousePosition();
        _screenSize = new ScreenSize();
        _tilesSize = new TilesSize();
        _engine_context = new EngineContext();
        _engine_context->inputHandler = new services::InputHandler();

        spdlog::info("Initializing Hyperion Engine");
        this->initializeConsole();
    }

    void HyperionEngine::initializeConsole() {
        spdlog::info("Initializing console");
        auto params = TCOD_ContextParams{};

        _engine_context->inputHandler->subscribeKeystroke("CTRL+q", [this](SDL_Keycode key, std::string keystroke) {
            spdlog::info("CTRL+Q pressed: Key:{} keystroke:{}", key, keystroke);
            this->_running = false;
        });

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

        _tilesSize->height = defaultTileset.get_tile_height();
        _tilesSize->width = defaultTileset.get_tile_width();

        _screenSize->width = _options->columns * _tilesSize->width;
        _screenSize->height = _options->rows * _tilesSize->height;

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

        tcod::print(*this->_rootConsole, {10, 12},
                    std::format("mouse x: {} y:{} leftclicked: {} right:{}", this->_mousePosition->x,
                                this->_mousePosition->y, this->_mousePosition->leftButton,
                                this->_mousePosition->rightButton),
                    TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_LEFT);

        tcod::print(*this->_rootConsole, {10, 13},
                    std::format("mouse grid x: {} y:{}",
                                this->_mousePosition->gridX,
                                this->_mousePosition->gridY),
                    TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_LEFT);
    }

    void HyperionEngine::update_inputs(SDL_Event *event) {
        if (event->type == SDL_MOUSEMOTION) {
            this->_mousePosition->x = event->motion.x;
            this->_mousePosition->y = event->motion.y;

            this->_mousePosition->gridX = event->motion.x / _tilesSize->width;
            this->_mousePosition->gridY = event->motion.y / _tilesSize->height;
        }

        if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                this->_mousePosition->leftButton = true;
            }
            if (event->button.button == SDL_BUTTON_RIGHT) {
                this->_mousePosition->rightButton = true;
            }

            if (event->button.button == SDL_BUTTON_MIDDLE) {
                this->_mousePosition->middleButton = true;
            }
        }

        if (event->type == SDL_MOUSEBUTTONUP) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                this->_mousePosition->leftButton = false;
            }
            if (event->button.button == SDL_BUTTON_RIGHT) {
                this->_mousePosition->rightButton = false;
            }
            if (event->button.button == SDL_BUTTON_MIDDLE) {
                this->_mousePosition->middleButton = false;
            }
        }


        this->_engine_context->inputHandler->update(event);
    }


    void HyperionEngine::update(SDL_Event *event) {
        this->update_inputs(event);
    }


    void HyperionEngine::run() {
        SDL_Event event;


        while (this->_running) {
            this->_lastUpdate = this->_currentTick;
            this->_currentTick = SDL_GetPerformanceCounter();
            this->_deltaTime = (this->_currentTick - this->_lastUpdate) * 1000 / SDL_GetPerformanceFrequency();

            this->_rootConsole->clear();
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    this->_running = false;
                }
                this->update(&event);
            }
            this->render();

            this->_context.present(*this->_rootConsole);
        }
    }


    HyperionEngine::~HyperionEngine() {
        delete _options;
        delete _rootConsole;
    }
}
