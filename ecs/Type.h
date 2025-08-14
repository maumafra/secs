#ifndef TYPE_H
#define TYPE_H

#include "definitions.h"
#include "datastructures/hash.h"

typedef struct {
    std::vector<ComponentId> ids;       /* Array with components ids */
    int32_t count;                      /* Num of elements in array */
} Type;

#endif