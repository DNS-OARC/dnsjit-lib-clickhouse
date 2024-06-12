#include "config.h"

#include <clickhouse/client.h>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.column");

#define self ((ColumnRef*)_self)

lib_clickhouse_column_t* lib_clickhouse_column_new(enum lib_clickhouse_column_type type)
{
    ColumnRef* column;

    switch (type) {
    case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
        column = new ColumnRef(std::make_shared<ColumnUInt64>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
        column = new ColumnRef(std::make_shared<ColumnString>());
        break;
    default:
        mlfatal("invalid type");
    }

    return (lib_clickhouse_column_t*)column;
}

void lib_clickhouse_column_delete(lib_clickhouse_column_t* _self)
{
    delete self;
}

}