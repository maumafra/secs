#include "World.cpp"

#include <iostream>
#include <typeinfo>

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
    World ecs;
    auto e = ecs.spawn();
    auto e2 = ecs.spawn();



    //ComponentId arr1[] = {1, 2, 5, 10, 12};
    //ComponentId arr2[] = {1, 2, 5, 10, 12};
    //Type* t1 = new Type();
    //t1->ids = arr1;
    //t1->count = (int32_t)(sizeof(arr1) / sizeof(arr1[0]));
    //Type* t2 = new Type();
    //t2->ids = arr2;
    //t2->count = (int32_t)(sizeof(arr2) / sizeof(arr2[0]));
    //std::cout << "start hash 1" << std::endl;
    //uint64_t i1 = typeHash(t1);
    //std::cout << i1 << std::endl;
    //std::cout << "start hash 2" << std::endl;
    //uint64_t i2 = typeHash(t2);
    //std::cout << i2 << std::endl;
    //delete t1;
    //delete t2;
    //Pos *po1 = new Pos();
    //Pos *po2 = new Pos();
    //std::cout << typeid(*po1).hash_code() <<std::endl;
    //std::cout << typeid(*po2).hash_code() <<std::endl;
    //delete po1;
    //delete po2;
    return 0;
}