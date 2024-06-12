#include "config.h"

#include <clickhouse/block.h>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.block");

#define self ((Block*)_self)

lib_clickhouse_block_t* lib_clickhouse_block_new()
{
    return (lib_clickhouse_block_t*)new Block();
}

void lib_clickhouse_block_delete(lib_clickhouse_block_t* _self)
{
    mlassert_self();
    delete self;
}

void lib_clickhouse_block_append_column(lib_clickhouse_block_t* _self, const char* name, lib_clickhouse_column_t* column)
{
    mlassert_self();
    self->AppendColumn(name, *(ColumnRef*)column);
}

}