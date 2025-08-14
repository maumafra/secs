#include "definitions.h"

struct ColumnBase {
    virtual ~ColumnBase() = default;
};

template<typename T>
struct Column : ColumnBase {
    std::vector<T> data;            /* Array with component data */
    size_t size() const override {  /* Size of the component data */
        return data.size();
    }           
};

// Table === Archetype
struct Table {
    uint32_t id;                                            /* Table id */

    std::vector<ComponentId> type;                          /* Components ids */
    std::vector<EntityId> entities;                         /* Entity ids */
    std::vector<ColumnBase*> columns;             /* Component data */

    //unordered_map<ComponentId, Table&> edges;

    ~Table() {
        for (ColumnBase* c : columns) {
            delete c;
        }
    };
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