#ifndef UPDATABLE_ENTITY_H
#define UPDATABLE_ENTITY_H

namespace hyperion::engine::entities {
    class UpdatableEntity {
    public:
        virtual void update(double deltaTime) = 0;
    };
}

#endif //UPDATABLE_ENTITY_H
