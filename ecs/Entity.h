#include "definitions.h"

struct Entity {
    EntityId id;

    Entity();

    explicit Entity(EntityId id);

    template <typename Func>
    Entity& add(const Func& func);
};