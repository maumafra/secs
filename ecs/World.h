#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <iostream>

#include "TableFunctions.cpp"
#include "TypeFunctions.cpp"
#include "Entity.h"
#include "IdStorage.h"

using namespace std;

using TableMap = unordered_map<uint32_t, TableRecord*>;

struct World {
    World();

    void initWorld();

    Entity& spawn();

    template <typename T>
    Entity& addComponent(EntityId id, T t);

    Record* createRecord(EntityId entity, Table* table);

    Table* getTable(const Type* type);

    Table* createTable(const Type* type);

    void saveTable(TypeHash typeHash, Table* table);

    //bool hasComponent(EntityId entity, ComponentId component);
    //void* getComponent(EntityId entity, ComponentId component);
    //void add(EntityId entity, ComponentId component);
//
    //void addEdges(Table& Table, ComponentId component);

    // finds the Table of an entity
    unordered_map<EntityId, Record*> entity_index;

    // finds the Table by its list of components
    unordered_map<TypeHash, Table*> table_index;

    // finds the archetypes that has the component
    unordered_map<ComponentId, TableMap*> component_index;

    EntityIdIndex *entityIdIndex;
};

#endif