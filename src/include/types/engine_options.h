//
// Created by squid on 5/16/24.
//

#ifndef ENGINE_OPTIONS_H
#define ENGINE_OPTIONS_H
#include <libtcod.hpp>

namespace hyperion::engine {
    typedef struct {
        int argc;
        char **argv;
        const char *windowTitle;
        bool fullscreen;
        bool resizable;
        bool vsync;
        int columns;
        int rows;
        double tileSetScale = 1.0;
        const char *dataDirectory;
        const char *tilesetName;
        TCOD_renderer_t renderer;
    } EngineOptions;
}

#endif //ENGINE_OPTIONS_H
