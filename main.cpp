#include "definitions.h"
#include "TypeFunctions.cpp"

#include <iostream>

struct Pos {
    float x, y;
};

int main() {
    //nebula::ecs::World *world = new nebula::ecs::World();
    //world->spawn([](Pos *pos){
    //    pos->x = 5.0f;
    //    pos->y = 1.0f;
    //});
    /* ^ I think this should:
        -> Create new entity (new id) / later: use unalived entities' indexes
        -> Create new type (and hashing it)
        -> Create new table (save all data in there)
        -> Populate all world indexes
    */
    ComponentId arr1[] = {1, 2, 5};
    Type* t = new Type();
    t->ids = arr1;
    t->count = 3;
    std::cout << "start hash " << std::endl;
    uint64_t i = typeHash(t);
    std::cout << i << std::endl;
    delete t;
    return 0;
}