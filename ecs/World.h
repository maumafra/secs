#ifndef WORLD_H
#define WORLD_H

#include "definitions.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "Table.h"
#include "Type.h"
#include "Entity.h"




namespace nebula {
    namespace ecs {

using namespace std;

using TableMap = unordered_map<uint32_t, TableRecord*>;

struct World {
    template <typename Func>
    Entity spawn(Func func);



    bool hasComponent(EntityId entity, ComponentId component);
    void* getComponent(EntityId entity, ComponentId component);
    void add(EntityId entity, ComponentId component);

    void addEdges(Table& Table, ComponentId component);


    private:

    EntityId getNewEntityIndex();

    EntityId entity_id_index = 0;

    // finds the Table of an entity
    unordered_map<EntityId, Record*> entity_index;

    // finds the Table by its list of components
    //unordered_map<Type, Table*> table_index;

    // finds the archetypes that has the component
    unordered_map<ComponentId, TableMap*> component_index;
};
} //ecs
} //nebula

#endif