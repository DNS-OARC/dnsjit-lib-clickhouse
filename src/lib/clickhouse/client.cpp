#include "config.h"

#include "client.h"

#include <clickhouse/client.h>

#include <stdexcept>
#include <iostream>

using namespace clickhouse;

extern "C" {

#include <dnsjit/core/log.h>

#define self ((Client*)_self)

clickhouse_client_t* clickhouse_client_new(const clickhouse_client_options_t* options)
{
    Client* client;

    try {
        gldebug("lib.clickhouse.client connecting");
        client = new Client(*(ClientOptions*)options);

        gldebug("lib.clickhouse.client current endpoint: %s", client->GetCurrentEndpoint().value().host.c_str());
    } catch (const std::exception& e) {
        glcritical("lib.clickhouse.client exception: %s", e.what());
    }

    return (clickhouse_client_t*)client;
}

void clickhouse_client_execute(clickhouse_client_t* _self, const char* query)
{
    gldebug("lib.clickhouse.client execute: %s", query);
    self->Execute(query);
}

void clickhouse_client_select(clickhouse_client_t* _self, const char* query)
{
    gldebug("lib.clickhouse.client select: %s", query);
    self->Select(query, [](const Block& block)
        {
            for (size_t row = 0; row < block.GetRowCount(); ++row) {
                for (size_t col = 0; col < block.GetColumnCount(); col++) {
                    std::cout << block.GetColumnName(col) << " " << block[col]->Type()->GetName() << " ";

                    switch (block[col]->Type()->GetCode()) {
                    case Type::Code::UInt64:
                        std::cout << block[col]->As<ColumnUInt64>()->At(row);
                        break;
                    case Type::Code::String:
                        std::cout << block[col]->As<ColumnString>()->At(row);
                        break;
                    default:
                        break;
                    }

                    std::cout << std::endl;
                }
            }
        }
    );
}

void clickhouse_client_destroy(clickhouse_client_t* _self)
{
    delete self;
}

}