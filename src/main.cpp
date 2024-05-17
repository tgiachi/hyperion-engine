#include <iostream>

#include "include/engine/hyperion_engine.h"


auto get_data_dir() -> std::filesystem::path {
    static auto root_directory = std::filesystem::path{"."};
    while (!exists(root_directory / "data")) {
        root_directory /= "..";
        if (!exists(root_directory)) {
            throw std::runtime_error("Could not find the data directory.");
        }
    }
    return root_directory / "data";
};

int main(int argc, char **argv) {
    auto engineOptions = hyperion::engine::EngineOptions{};
    engineOptions.argc = argc;
    engineOptions.argv = argv;
    engineOptions.windowTitle = "Hyperion Engine";
    engineOptions.fullscreen = false;
    engineOptions.resizable = true;
    engineOptions.vsync = false;
    engineOptions.columns = 80;
    engineOptions.rows = 50;
    engineOptions.tileSetScale = 2.0;
    engineOptions.renderer = TCOD_RENDERER_OPENGL2;
    engineOptions.tilesetName = "tilesets/dejavu10x10_gs_tc.png";
    engineOptions.tilesSetHeight = 8;
    engineOptions.tilesSetWidth = 32;

    //engineOptions.tilesetName = "tilesets/DB_curses_12x12.png";
    //engineOptions.tilesSetHeight = 32;
    //engineOptions.tilesSetWidth = 32;
    engineOptions.dataDirectory = get_data_dir().c_str();

    auto engine = hyperion::engine::HyperionEngine(engineOptions);

    engine.run();

    return 0;
}
