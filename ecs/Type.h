#ifndef TYPE_H
#define TYPE_H

#include "definitions.h"
#include "datastructures/hash.h"

#include <algorithm>
#include <iostream>

typedef struct _ {
    std::vector<ComponentId> ids;       /* Array with components ids */

    _() {};
    _(std::vector<ComponentId> t_ids) : ids(t_ids) {};
} Type;

#endif