#include "Entity.h"

Entity::Entity()
    : id(0)
{
};

Entity::Entity(EntityId id) {
    this->id = id;
};

template <typename Func>
Entity& Entity::add(const Func& func) {

    return this;
};
