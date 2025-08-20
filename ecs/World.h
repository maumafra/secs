#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "TableFunctions.cpp"
#include "TypeFunctions.cpp"
#include "Entity.h"
#include "IdStorage.h"

using namespace std;

using TableMap = unordered_map<TableId, TableRecord*>;

struct World {
    World();

    void initWorld();

    EntityId spawn();

    template <typename T>
    void addComponent(EntityId id, T t);

    template <typename T>
    T* getComponent(EntityId id);

    Record* createRecord(EntityId entity, Table* table);

    Table* getTable(const Type type);

    Table* createTable(const Type type, Table* oldTable) ;

    void saveTable(const Type type, Table* table);

    bool hasComponent(EntityId entity, ComponentId component);

    void moveTableComponents(const EntityId eId, const uint32_t entRow, Table* oldTable, Table* newTable);

    bool tableHasComponent(ComponentId id, Table* table);

    uint32_t getComponentColumn(ComponentId id, Table* table);

    void saveComponentColumn(ComponentId id, Table* table, uint32_t index);

    void saveComponentTable(ComponentId id, Table* table);

    void rearrangeTableEntities(Table* table, const uint32_t idxStart);

    void print();

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
    ComponentIdIndex *componentIdIndex;
};

#endif