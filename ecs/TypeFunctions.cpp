#include "Type.h"

static
uint64_t typeHash(const Type* type) {
    const void* ids = static_cast<const void*>(type->ids.data());
    int32_t count = type->count;
    return ecs_hash(ids, count * ((uint32_t)sizeof(ecsId)));
};
