#include "Definitions.hpp"
#include "Hash.hpp"

#include <algorithm>

static inline TypeHash typeHash(const Type type) {
    const void* ids = static_cast<const void*>(type.data());
    int32_t count = (int32_t)type.size();
    return ecs_hash(ids, count * ((uint32_t)sizeof(ecsId)));
};

static inline Type getNewType(const Type oldType, ComponentId newId) {
    Type new_ids (oldType);
    new_ids.emplace_back(newId);
    std::sort(new_ids.begin(), new_ids.end());

    //DEBUG print sorted vector
    //for (ComponentId id : new_ids) {
    //    std::cout << id << " ";
    //}
    //std::cout << std::endl;
    return Type(new_ids);
};