#include "World.h"

namespace nebula {
    namespace ecs {

EntityId World::getNewEntityIndex() {
    return entity_id_index++;
}

template <typename Func>
Entity World::spawn(Func func) {
    EntityId id = getNewEntityIndex();
    std::cout << "New entity id: " << id;
    void* ptr;
    func(ptr);
    //create type
    //create table
    return nullptr;
}

//bool World::hasComponent(EntityId entity, ComponentId component) {
//    Record& record = entity_index[entity];
//    Table& table = record.table;
//
//    ArchetypeMap& archetypeMap = component_index[component];
//    return archetypeMap.count(table.id) != 0;
//}
//
//void* World::getComponent(EntityId entity, ComponentId component) {
//    Record& record = entity_index[entity];
//    Table& table = record.table;
//
//    ArchetypeMap& archetypeMap = component_index[component];
//    if (archetypeMap.count(table.id) == 0) {
//        return nullptr;
//    }
//    // TODO: try removing the block above and test the record to check if it exists
//    ArchetypeRecord& a_record = archetypeMap[table.id];
//    Column* c = &table.columns->at(a_record.column);
//    return (void*)(((uintptr_t)(c->data)) + ((uintptr_t)(record.row * c->data_size)));
//}
//
//void World::add(EntityId entity, ComponentId component) {
//    Record& record = entity_index[entity];
//    Table& table = record.table;
//    if (table.edges.count(component) == 0) {
//        addEdges(table, component);
//    }
//    Table& nextArchetype = table.edges[component].add;
//    //moveEntity(table, record.row, nextArchetype);
//}
//
////void World::moveEntity(Table& table, size_t row, Table& nextArchetype) {
////
////}
//
//// maybe specify if the edge is for add or remove
//void World::addEdges(Table& table, ComponentId component) {
//    // find existing archetypes or create new
//    // populate the edge
//    ArchetypeMap& archetypeMap = component_index[component];
//    if (archetypeMap.count(table.id) == 0) {
//        // create new Table
//    }
//    // search archetype_index with new type (old type + new component) maybe
//}

}// ecs
}// nebula
