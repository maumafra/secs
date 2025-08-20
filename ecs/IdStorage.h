#include "definitions.h"

#include <unordered_map>
#include <typeinfo>
#include <string>
#include <set>

struct EntityIdIndex {
    EntityId nextId;
    std::set<EntityId> unalivedIds;
};

struct ComponentIdIndex {
    ComponentId nextId = 1;
    std::unordered_map<std::string, ComponentId> typeIdIndex;
};

template <typename T>
inline ComponentId getNewId(ComponentIdIndex *index) {
    ComponentId id = index->nextId ++;
    index->typeIdIndex.insert({std::string(typeid(T).name()), id});
    return id;
};

template <typename T>
inline ComponentId getComponentId(ComponentIdIndex *index) {
    if (index->typeIdIndex.count(std::string(typeid(T).name())) == 0) {
        return 0;
    }
    return index->typeIdIndex[std::string(typeid(T).name())];
};

EntityId getNewId(EntityIdIndex *index);

void setIdUnalived(EntityIdIndex *index, EntityId id);