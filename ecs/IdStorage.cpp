#include "IdStorage.hpp"

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
}