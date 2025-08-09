#include <cstdint>

#include "definitions.h"

struct Column {
    void* data;                 /* Array with component data */
    size_t data_size;           /* Size of the component data */
};

// Table === Archetype
struct Table {
    uint32_t id;                /* Table id */
    uint32_t row_count;         /* Number of entities */
    uint32_t column_count;      /* Number of components */

    ComponentId *type;          /* Components ids */
    EntityId *entities;         /* Entity ids */
    Column *columns;            /* Component data */

    //unordered_map<ComponentId, Table&> edges;
};

//struct TableEdge {
//  Table& add;
//  Table& remove;
//};

struct Record {
    Table* table;               /* Pointer for Entity table */
    uint32_t row;               /* Entity row in the table */
};

struct TableRecord {
    uint32_t column;            /* Component column in the table */
};