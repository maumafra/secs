#pragma once

#include "Definitions.hpp"

#include <unordered_map>
#include <typeinfo>
#include <string>
#include <set>

struct EntityIdIndex {
    EntityId nextId;
    std::set<EntityId> unalivedIds;
};

struct ComponentIdIndex {
    ComponentId nextId = 1; //lazy way to check if a component exists, since no component will be registered with an id of 0
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

EntityId getNewId(EntityIdIndex *index) {
    if (index->unalivedIds.size() != 0) {
        /* Use unalived id */
        EntityId id = *index->unalivedIds.begin();
        index->unalivedIds.erase(index->unalivedIds.begin());
        return id;
    }

    EntityId id = index->nextId ++;
    return id;
};

void setIdUnalived(EntityIdIndex *index, EntityId id) {
    index->unalivedIds.insert(id);
};

bool isIdUnalived(EntityIdIndex *index, EntityId id) {
    if (*index->unalivedIds.end() == id) {
        return true;
    }
    return *index->unalivedIds.find(id) == id;
};