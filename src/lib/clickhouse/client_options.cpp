#include "config.h"

#include "client_options.h"

#include <clickhouse/client.h>

#include <stdexcept>

using namespace clickhouse;

extern "C" {

#include <dnsjit/core/log.h>

#define self ((ClientOptions*)_self)

clickhouse_client_options_t* clickhouse_client_options_new()
{
    ClientOptions* options = new ClientOptions();

    try {
        options->SetHost("localhost");
        options->SetPort(9000);
        options->SetUser("default");
        options->SetPassword("");
        options->SetDefaultDatabase("default");
    } catch (const std::exception& e) {
        glfatal("lib.clickhouse.client_options exception: %s", e.what());
    }

    return (clickhouse_client_options_t*)options;
}

int clickhouse_client_options_set(clickhouse_client_options_t* _self, enum clickhouse_client_option option, const char* str, double num)
{
    try {
        switch (option) {
        case CLICKHOUSE_CLIENT_OPTION_HOST:
            self->SetHost(str);
            break;
        case CLICKHOUSE_CLIENT_OPTION_PORT:
            self->SetPort(num);
            break;
        case CLICKHOUSE_CLIENT_OPTION_USER:
            self->SetUser(str);
            break;
        case CLICKHOUSE_CLIENT_OPTION_PASSWORD:
            self->SetPassword(str);
            break;
        case CLICKHOUSE_CLIENT_OPTION_DEFAULT_DATABASE:
            self->SetDefaultDatabase(str);
            break;
        default:
            return -1;
        }
    } catch (const std::exception& e) {
        glwarning("lib.clickhouse.client_options error: %s", e.what());
        return -1;
    }
    return 0;
}

void clickhouse_client_options_destroy(clickhouse_client_options_t* _self)
{
    delete self;
}

}