#include "definitions.h"

#include "Type.h"
#include "datastructures/hash.h"

static
uint64_t typeHash(const void* ptr) {
    const Type *type = static_cast<const Type*>(ptr);
    ecsId* ids = type->ids;
    int32_t count = type->count;
    return ecs_hash(ids, count * sizeof(ecsId));
};
