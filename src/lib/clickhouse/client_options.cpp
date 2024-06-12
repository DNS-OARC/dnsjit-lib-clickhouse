#include "config.h"

#include <clickhouse/client.h>

#include <stdexcept>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.client_options");

#define self ((ClientOptions*)_self)

lib_clickhouse_client_options_t* lib_clickhouse_client_options_new()
{
    ClientOptions* options = new ClientOptions();

    try {
        options->SetHost("localhost");
        options->SetPort(9000);
        options->SetUser("default");
        options->SetPassword("");
        options->SetDefaultDatabase("default");
    } catch (const std::exception& e) {
        mlfatal("exception: %s", e.what());
    }

    return (lib_clickhouse_client_options_t*)options;
}

void lib_clickhouse_client_options_delete(lib_clickhouse_client_options_t* _self)
{
    mlassert_self();
    delete self;
}

int lib_clickhouse_client_options_set(lib_clickhouse_client_options_t* _self, enum lib_clickhouse_client_option option, const char* str, double num)
{
    mlassert_self();
    try {
        switch (option) {
        case LIB_CLICKHOUSE_CLIENT_OPTION_HOST:
            self->SetHost(str);
            break;
        case LIB_CLICKHOUSE_CLIENT_OPTION_PORT:
            self->SetPort(num);
            break;
        case LIB_CLICKHOUSE_CLIENT_OPTION_USER:
            self->SetUser(str);
            break;
        case LIB_CLICKHOUSE_CLIENT_OPTION_PASSWORD:
            self->SetPassword(str);
            break;
        case LIB_CLICKHOUSE_CLIENT_OPTION_DEFAULT_DATABASE:
            self->SetDefaultDatabase(str);
            break;
        default:
            return -1;
        }
    } catch (const std::exception& e) {
        mlwarning("exception: %s", e.what());
        return -1;
    }
    return 0;
}

}