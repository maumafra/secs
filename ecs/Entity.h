#include "definitions.h"

struct Entity {
    EntityId id;

    Entity() {};
    explicit Entity(EntityId id) : id(id) {};
};