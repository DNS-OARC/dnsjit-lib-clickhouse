#include "config.h"

#include <dnsjit/core/assert.h>
#include <dnsjit/core/log.h>

void* clickhouse_glue_new_client();

typedef struct lib_clickhouse {
    core_log_t _log;

    void* cli;
} lib_clickhouse_t;

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
    self->cli = clickhouse_glue_new_client();
}

void lib_clickhouse_destroy(lib_clickhouse_t* self)
{
    mlassert_self();
}
