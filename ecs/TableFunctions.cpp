#include "Table.h"

static
Table* createEmptyTable() {
    Table *t = new Table();
    t->id = 0;
    t->type = {};
    t->entities = {};
    t->columns = {};
    return t;
};