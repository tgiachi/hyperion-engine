#ifndef RENDABLE_ENTITY_H
#define RENDABLE_ENTITY_H

#include "libtcod.hpp"

namespace hyperion::engine::entities {
    class RendableEntity {
    public:
        virtual void render(tcod::Console* console) = 0;
    };
}

#endif //RENDABLE_ENTITY_H
