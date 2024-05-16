//
// Created by squid on 5/16/24.
//

#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H
#include "../engine/input_handler.h"
#include "../engine/data_loader.h"

namespace hyperion::engine {
    typedef struct {
        services::InputHandler *inputHandler;
        services::DataLoader *dataLoader;
    } EngineContext;
}


#endif //ENGINE_CONTEXT_H
