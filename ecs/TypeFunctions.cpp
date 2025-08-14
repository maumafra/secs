#include "Type.h"

static
uint64_t typeHash(const Type* type) {
    const void* ids = static_cast<const void*>(type->ids.data());
    int32_t count = (int32_t)type->ids.size();
    return ecs_hash(ids, count * ((uint32_t)sizeof(ecsId)));
};

static
Type* getNewType(const Type *oldType, ComponentId newId) {
    std::vector<ComponentId> new_ids (oldType->ids);
    new_ids.emplace_back(newId);
    std::sort(new_ids.begin(), new_ids.end());

    //DEBUG print sorted vector
    for (ComponentId id : new_ids) {
        std::cout << id << " ";
    }
    return new Type(new_ids);
};