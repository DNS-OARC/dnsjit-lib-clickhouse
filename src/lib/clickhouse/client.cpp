#include "config.h"

#include "client.h"

#include <clickhouse/client.h>

#include <stdexcept>

using namespace clickhouse;

extern "C" {

#include <dnsjit/core/log.h>

clickhouse_client_t* clickhouse_client_new(const clickhouse_client_options_t* options)
{
    Client* client;

    try {
        client = new Client(*(ClientOptions*)options);

        glinfo("current endpoint: %s", client->GetCurrentEndpoint().value().host.c_str());
    } catch (const std::exception& e) {
        glcritical("lib.clickhouse.client exception: %s", e.what());
    }

    return (clickhouse_client_t*)client;
}

void clickhouse_client_destroy(clickhouse_client_t* client)
{
    delete (Client*)client;
}

}