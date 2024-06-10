#include "config.h"

#include <clickhouse/client.h>

#include <stdexcept>
#include <iostream>

using namespace clickhouse;

extern "C" {

void* clickhouse_glue_new_client()
{
    Client* client;

    try {
        const auto localHostEndpoint = ClientOptions()
            .SetHost("localhost")
            .SetPort(9000)
            .SetUser("default")
            .SetPassword("")
            .SetDefaultDatabase("default");

        client = new Client(ClientOptions(localHostEndpoint));

        std::cout << "current endpoint : " <<  client->GetCurrentEndpoint().value().host << "\n";
    } catch (const std::exception& e) {
        std::cerr << "exception : " << e.what() << std::endl;
    }

    return client;
}

}