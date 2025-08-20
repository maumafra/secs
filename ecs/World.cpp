#include "World.h"

World::World() 
    : entity_index(NULL)
    , component_index(NULL) 
    , entityIdIndex(nullptr) {
    
    initWorld();
}

void World::initWorld() {
    entityIdIndex = new EntityIdIndex();
    componentIdIndex = new ComponentIdIndex();
    Table* emptyTable = createEmptyTable();
    this->saveTable({}, emptyTable);
}

EntityId World::spawn() {
    EntityId id = getNewId(this->entityIdIndex);
    Table *t = this->table_index[0];
    Record *r = this->createRecord(id, t);
    this->entity_index[id] = r;
    return id;
}

template <typename T>
T* World::getComponent(EntityId id) {
    if(this->entity_index.count(id) == 0) { // Entity does not exist
        return nullptr;
    }
    Record *r = this->entity_index[id];
    ComponentId c_id = getComponentId<T>(this->componentIdIndex);
    if (!c_id) { // Component does not exist
        return nullptr; 
    }
    Table* table = r->table;
    TableMap* tabMap = this->component_index[c_id];
    if (tabMap->count(table->id) == 0) { // Entity does not have this component
        return nullptr;
    }
    TableRecord* tabRec = tabMap->at(table->id);
    Column<T>* col = (Column<T>*)table->columns.at(tabRec->column);
    return &col->data.at(r->row);
}

template <typename T>
void World::addComponent(EntityId id, T t) {
    if(this->entity_index.count(id) == 0) { // Entity does not exist
        return;
    }
    Record *r = this->entity_index[id];
    ComponentId c_id = getComponentId<T>(this->componentIdIndex);
    if(!c_id) { // Component not yet registered
        c_id = getNewId<T>(this->componentIdIndex); // So register it here
        this->component_index.insert({c_id, new TableMap()}); // Saving it on component_index
    }
    if(this->hasComponent(id, c_id)) { // Entity already has this component
        // So override its value
        return;
    }
    // Entity does not have this component, which means we need to:
    // -> check if there is a table with those components
    //    -> if so, move the entity to this table
    //    -> if not, create a new table and then move the entity
    // -> delete the entity data on the old table
    // -> update entity data in entity_index
    // -> create component data in component_index for the new table
    //TODO if not check/create edges

    // v This could be the move_entity func
    uint32_t ent_index = r->row;
    Table *oldTable = r->table;
    Type oldType = oldTable->type;
    Type newType = getNewType(oldType, c_id);
    Table* newTable = getTable(newType);
    if (!newTable) {
        newTable = this->createTable(newType, oldTable);
        this->saveTable(newType, newTable);
    }
    this->moveTableComponents(id, ent_index, oldTable, newTable);
    oldTable->entities.erase(oldTable->entities.begin() + ent_index); // Check
    this->rearrangeTableEntities(oldTable, ent_index);
    ent_index = newTable->entities.size();

    if (this->tableHasComponent(c_id, newTable)) {
        uint32_t compIndex = this->getComponentColumn(c_id, newTable);
        Column<T>* col = (Column<T>*)newTable->columns.at(compIndex);
        col->data.emplace_back(t);
    } else {
        uint32_t index = newTable->columns.size();
        Column<T>* col = new Column<T>();
        col->data.emplace_back(t);
        newTable->columns.emplace_back(col);
        this->saveComponentColumn(c_id, newTable, index);
    }
    r->row = ent_index;
    r->table = newTable;
    newTable->entities.emplace_back(id);
}

void World::rearrangeTableEntities(Table* table, const uint32_t idxStart) {
    for (uint32_t i = idxStart; i < table->entities.size(); i++) { // Check if there is a better way to do this
        EntityId id = table->entities.at(i);
        Record* entRec = this->entity_index.at(id);
        entRec->row = i;
    }
}

void World::moveTableComponents(const EntityId eId, const uint32_t entRow, Table* oldTable, Table* newTable) {
    for (ComponentId cId : oldTable->type) {
        // get component index on the table
        uint32_t compIndex = this->getComponentColumn(cId, oldTable);

        // get component column
        ColumnBase* oldCol = oldTable->columns.at(compIndex);
        ColumnBase* newCol;

        if (this->tableHasComponent(cId, newTable)) {
            uint32_t newCompIndex  = this->getComponentColumn(cId, newTable);
            newCol = newTable->columns.at(newCompIndex);
        } else {
            uint32_t index = newTable->columns.size();
            newCol = oldCol->createClone();
            newTable->columns.emplace_back(newCol);
            this->saveComponentColumn(cId, newTable, index);
        }
        oldCol->moveData(newCol, entRow);
    }
};

void World::saveComponentColumn(ComponentId id, Table* table, uint32_t index) {
    TableMap *tabMap = this->component_index[id];
    TableRecord *tabRec = new TableRecord();
    tabRec->column = index;
    tabMap->insert({table->id, tabRec});
}

bool World::tableHasComponent(ComponentId id, Table* table) {
    TableMap *tabMap = this->component_index[id];
    return tabMap->count(table->id) != 0;
}

uint32_t World::getComponentColumn(ComponentId id, Table* table) {
    TableMap *tabMap = this->component_index[id];
    TableRecord *tabRec = tabMap->at(table->id);
    return tabRec->column;
}

Record* World::createRecord(EntityId entity, Table* table) {
    uint32_t recRow = table->entities.size();
    table->entities.push_back(entity);
    Record* r = new Record();
    r->row = recRow;
    r->table = table;
    return r;
}

Table* World::getTable(const Type type) {
    TypeHash th = 0;
    if (type.size() != 0) {
        th = typeHash(type);
    }
    if (this->table_index.count(th) == 0) {
        return nullptr;
    }
    Table *t = this->table_index[th];
    return t;
}

Table* World::createTable(const Type type, Table* oldTable) {
    Table *t = new Table();
    t->id = getNewId(this->entityIdIndex); //TODO: Work on this later
    t->type = type;
    t->columns = {};
    return t;
}

void World::saveTable(const Type type, Table* table) {
    TypeHash th = 0;
    if (type.size() != 0) {
        th = typeHash(type);
    }
    table_index.insert({th, table});
}

bool World::hasComponent(EntityId entity, ComponentId component) {
    Record *record = entity_index[entity];
    Table *table = record->table;
    if (component_index.count(component) == 0) {
        return false;
    }
    TableMap *archetypeMap = component_index[component];
    return archetypeMap->count(table->id) != 0;
}

void World::print() {
    std::cout << "---- ENTITY INDEX ----" << std::endl;
    for (auto const &entPair : this->entity_index) {
        Record* r = entPair.second;
        std::cout << "Entity: " << entPair.first << " Table: " << r->table->id << " at " << r->row << std::endl; 
    }
    std::cout << "---- TABLE INDEX ----" << std::endl;
    for (auto const &tabPair : this->table_index) {
        std::cout << "Table: " << tabPair.second->id << "\n";
        std::cout << "      > Hash: " << tabPair.first << "\n";
        std::cout << "      > Entities (" << tabPair.second->entities.size() << "): ";
        for (EntityId entId : tabPair.second->entities) {
            std::cout << entId << " ";
        }
        std::cout << "\n";
        std::cout << "      > Components : ";
        for (ComponentId compId : tabPair.second->type) {
            std::cout << compId << " ";
        }
        std::cout << "\n";
    }
}
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
