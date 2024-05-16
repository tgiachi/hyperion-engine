#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "rendable_entity.h"
#include "updatable_entity.h"

namespace hyperion::engine::entities {
    class BaseEntity : public RendableEntity, public UpdatableEntity {
    public:
        void render(TCOD_Console console) override =0;

        void update(double deltaTime) override = 0;
    };
}

#endif //BASE_ENTITY_H
