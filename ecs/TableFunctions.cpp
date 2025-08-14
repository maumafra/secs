#include "Table.h"

static
Table* createEmptyTable() {
    Table *t = new Table();
    t->id = 0;
    return t;
};