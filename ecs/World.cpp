#include "World.h"

World::World() 
    : entity_index(NULL)
    , component_index(NULL) 
    , entityIdIndex(nullptr) {
    
    initWorld();
}

void World::initWorld() {
    entityIdIndex = new EntityIdIndex();
    Table* emptyTable = createEmptyTable();
    this->saveTable(0, emptyTable);
}

Entity& World::spawn() {
    EntityId id = getNewId(this->entityIdIndex);
    std::cout << "New entity id: " << id << std::endl;
    Entity *e = new Entity(id);
    Table *t = this->table_index[0];
    Record *r = this->createRecord(id, t);
    return *e;
}

template <typename T>
Entity& World::addComponent(EntityId id, T t) {
    Record *r = this->entity_index[id];
    if(!r) {
        return nullptr; //Entity does not exist
    }

    return nullptr;
}

Record* World::createRecord(EntityId entity, Table* table) {
    uint32_t recRow = table->entities.size();
    table->entities.push_back(entity);
    Record* r = new Record();
    r->row = recRow;
    return r;
}

Table* World::getTable(const Type* type) {
    TypeHash h = typeHash(type);
    Table *t = this->table_index[h];
    if (!t) {
        t = this->createTable(type);
        this->saveTable(h, t);
    }
    return t;
}

Table* World::createTable(const Type* type) {
    Table *t = new Table();
    t->id = 0; //TODO: Work on this later
    t->type = type->ids;
    return t;
}

void World::saveTable(TypeHash typeHash, Table* table) {
    table_index.insert({typeHash, table});
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
