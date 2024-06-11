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

int lib_clickhouse_set_host(lib_clickhouse_t* self, const char* host)
{
    mlassert_self();

    return clickhouse_client_options_set(self->options, CLICKHOUSE_CLIENT_OPTION_HOST, host, 0);
}

int lib_clickhouse_set_port(lib_clickhouse_t* self, double port)
{
    mlassert_self();

    return clickhouse_client_options_set(self->options, CLICKHOUSE_CLIENT_OPTION_PORT, 0, port);
}

void lib_clickhouse_connect(lib_clickhouse_t* self)
{
    mlassert_self();
    lassert(!self->client, "client is already connected");

    self->client = clickhouse_client_new(self->options);
}

void lib_clickhouse_execute(lib_clickhouse_t* self, const char* query)
{
    mlassert_self();
    lassert(self->client, "client is nil");

    clickhouse_client_execute(self->client, query);
}

void lib_clickhouse_select(lib_clickhouse_t* self, const char* query)
{
    mlassert_self();
    lassert(self->client, "client is nil");

    clickhouse_client_select(self->client, query);
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
