#include "IdStorage.h"

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

template <typename T>
ComponentId getNewId(T* c_type, ComponentIdIndex *index) {
    ComponentId id = index->nextId ++;
    index->typeIndex.insert({tipeid(c_type), id});
    return id;
};

template <typename T>
ComponentId getComponentId(T *c_type, ComponentIdIndex *index) {
    return index->typeIndex[tipeid(c_type)];
}

void setIdUnalived(EntityIdIndex *index, EntityId id) {
    index->unalivedIds.insert(id);
};

bool isIdUnalived(EntityIdIndex *index, EntityId id) {
    if (*index->unalivedIds.end() == id) {
        return true;
    }
    return *index->unalivedIds.find(id) == id;
}