#include "config.h"

#include "clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse");
static lib_clickhouse_t _defaults = {
    LOG_T_INIT_OBJ("dnsjit.lib.clickhouse")
};

core_log_t* lib_clickhouse_log()
{
    return &_log;
}

void lib_clickhouse_init(lib_clickhouse_t* self)
{
    mlassert_self();

    *self = _defaults;
}

void lib_clickhouse_destroy(lib_clickhouse_t* self)
{
    mlassert_self();
}
