#include "config.h"

#include "client_options.h"

#include <clickhouse/client.h>

#include <stdexcept>

using namespace clickhouse;

extern "C" {

#include <dnsjit/core/log.h>

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
        glcritical("lib.clickhouse.client_options exception: %s", e.what());
    }

    return (clickhouse_client_options_t*)options;
}

void clickhouse_client_options_destroy(clickhouse_client_options_t* options)
{
    delete (ClientOptions*)options;
}

}