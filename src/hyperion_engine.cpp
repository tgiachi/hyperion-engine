#include "include/engine/hyperion_engine.h"

#include <spdlog/spdlog.h>


#include "include/screen/test_screen.h"
#include "include/screen/screen_console.h"
#include "include/utils/image_scaler.h"
#include "include/screen/test_screen.h"

namespace hyperion::engine {
    HyperionEngine::HyperionEngine(const EngineOptions &options) {
        _options = options;
        _running = false;


        spdlog::info("Initializing Hyperion Engine");
        initializeConsole();
    }

    void HyperionEngine::initializeConsole() {
        spdlog::info("Initializing console");
        auto params = TCOD_ContextParams{};

        _engine_context.inputHandler.subscribeKeystroke("CTRL+q", [this](SDL_Keycode key, std::string keystroke) {
            spdlog::info("CTRL+Q pressed: Key:{} keystroke:{}", key, keystroke);
            _running = false;
        });

        _engine_context.inputHandler.subscribeKeystroke("CTRL+a", [this](SDL_Keycode key, std::string keystroke) {
            spdlog::info("CTRL+A pressed: Key:{} keystroke:{}", key, keystroke);
        });

        params.tcod_version = TCOD_COMPILEDVERSION;
        params.renderer_type = _options.renderer;
        params.vsync = _options.vsync;
        params.sdl_window_flags = _options.resizable ? SDL_WINDOW_RESIZABLE : 0;
        params.window_title = _options.windowTitle;


        auto tilesetPath = std::filesystem::path{_options.dataDirectory} / std::filesystem::path
                           {_options.tilesetName};

        if (_options.tileSetScale > 1.0) {
            spdlog::info("Scaling tileset by {}", _options.tileSetScale);
            auto newScaledFileName = (tilesetPath.c_str() + std::string("_scaled.png")).c_str();
            utils::images::scaleTileset(tilesetPath.c_str(), newScaledFileName,
                                        _options.tileSetScale);

            tilesetPath = newScaledFileName;
        }

        auto defaultTileset = tcod::load_tilesheet(tilesetPath, {_options.tilesSetWidth, _options.tilesSetHeight},
                                                   tcod::CHARMAP_TCOD);

        _tilesSize.height = defaultTileset.get_tile_height();
        _tilesSize.width = defaultTileset.get_tile_width();

        _screenSize.width = _options.columns * _tilesSize.width;
        _screenSize.height = _options.rows * _tilesSize.height;

        params.tileset = defaultTileset.get();


        _rootConsole = new tcod::Console{_options.columns, _options.rows};
        params.console = _rootConsole->get();
        _context = tcod::Context(params);
        _running = true;
    }

    void HyperionEngine::render() {
        tcod::print(*_rootConsole, {10, 10}, "Hello world", TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_LEFT);

        tcod::print(*_rootConsole, {10, 11}, std::format("delta: {}", _deltaTime),
                    TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_LEFT);

        tcod::print(*_rootConsole, {10, 12},
                    std::format("mouse x: {} y:{} leftclicked: {} right:{}", _mousePosition.x,
                                _mousePosition.y, _mousePosition.leftButton,
                                _mousePosition.rightButton),
                    TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_LEFT);

        tcod::print(*_rootConsole, {10, 13},
                    std::format("mouse grid x: {} y:{}",
                                _mousePosition.gridX,
                                _mousePosition.gridY),
                    TCOD_ColorRGB{255, 255, 255}, std::nullopt,
                    TCOD_LEFT);

        for (auto screenConsole: _screenConsoles) {
            screenConsole->render(_rootConsole->get());
        }
    }

    void HyperionEngine::update_inputs(const SDL_Event &event) {
        if (event.type == SDL_MOUSEMOTION) {
            _mousePosition.x = event.motion.x;
            _mousePosition.y = event.motion.y;

            _mousePosition.gridX = event.motion.x / _tilesSize.width;
            _mousePosition.gridY = event.motion.y / _tilesSize.height;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                _mousePosition.leftButton = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                _mousePosition.rightButton = true;
            }

            if (event.button.button == SDL_BUTTON_MIDDLE) {
                _mousePosition.middleButton = true;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                _mousePosition.leftButton = false;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                _mousePosition.rightButton = false;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                _mousePosition.middleButton = false;
            }
        }


        _engine_context.inputHandler.update(event);
    }


    void HyperionEngine::update(const SDL_Event &event) {
        if (event.type == SDL_QUIT) {
            _running = false;
        }


        update_inputs(event);

        for (auto *screenConsole: _screenConsoles) {
            screenConsole->update(_deltaTime);
        }
    }


    void HyperionEngine::run() {
        SDL_Event event;


        auto screen = screen::TestScreen(20, 10, 20, 20);
        _screenConsoles.push_back(&screen);


        _lastUpdate = SDL_GetTicks();


        while (_running) {
            auto currentTime = SDL_GetTicks();
            _deltaTime = currentTime - _lastUpdate;

            _rootConsole->clear();

            event = SDL_Event{};
            SDL_PollEvent(&event);
            update(event);
            render();
            _context.present(*_rootConsole);

            _lastUpdate = currentTime;;
        }
    }


    HyperionEngine::~HyperionEngine() {
    }
}
