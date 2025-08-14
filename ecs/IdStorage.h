#include "definitions.h"

#include <unordered_map>
#include <typeinfo>
#include <set>

using TypeInfoRef = std::reference_wrapper<const std::type_info>;

struct EntityIdIndex {
    EntityId nextId;
    std::set<EntityId> unalivedIds;
};

struct ComponentIdIndex {
    ComponentId nextId;
    std::unordered_map<TypeInfoRef, ComponentId> typeIndex;
};

template <typename T>
ComponentId getComponentId(T *t, ComponentIdIndex *index);

EntityId getNewId(EntityIdIndex *index);

void setIdUnalived(EntityIdIndex *index, EntityId id);