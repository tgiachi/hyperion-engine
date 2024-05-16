//
// Created by squid on 5/16/24.
//

#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H
#include "../engine/InputHandler.h"

namespace hyperion::engine {
    typedef struct {
        services::InputHandler *inputHandler;
    } EngineContext;
}


#endif //ENGINE_CONTEXT_H
