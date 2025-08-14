#include "definitions.h"
#include <set>

struct EntityIdIndex {
    EntityId nextId;
    std::set<EntityId> unalivedIds;
};



EntityId getNewId(EntityIdIndex *index);

void setIdUnalived(EntityIdIndex *index, EntityId id);