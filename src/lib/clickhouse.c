#include "config.h"

#include "clickhouse/client.h"

#include <dnsjit/core/assert.h>
#include <dnsjit/core/log.h>

typedef struct lib_clickhouse {
    core_log_t _log;

    clickhouse_client_options_t* options;
    clickhouse_client_t* client;
} lib_clickhouse_t;

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse");
static lib_clickhouse_t _defaults = {
    LOG_T_INIT_OBJ("dnsjit.lib.clickhouse"),
    0, 0
};

core_log_t* lib_clickhouse_log()
{
    return &_log;
}

void lib_clickhouse_init(lib_clickhouse_t* self)
{
    mlassert_self();

    *self = _defaults;
    self->options = clickhouse_client_options_new();
}

int lib_clickhouse_connect(lib_clickhouse_t* self)
{
    mlassert_self();

    if (self->client) {
        return -1;
    }

    self->client = clickhouse_client_new(self->options);

    return 0;
}

void lib_clickhouse_destroy(lib_clickhouse_t* self)
{
    mlassert_self();

    if (self->client) {
        clickhouse_client_destroy(self->client);
    }
    if (self->options) {
        clickhouse_client_options_destroy(self->options);
    }
}
