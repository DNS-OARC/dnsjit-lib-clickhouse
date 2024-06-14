#include "config.h"

#include <clickhouse/client.h>

#include <stdexcept>
#include <iostream>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.client");

#define self ((Client*)_self)

lib_clickhouse_client_t* lib_clickhouse_client_new(const lib_clickhouse_client_options_t* options)
{
    // TOOD: move connection to connect() func

    Client* client;

    try {
        mldebug("connecting");
        client = new Client(*(ClientOptions*)options);

        mldebug("current endpoint: %s", client->GetCurrentEndpoint().value().host.c_str());
    } catch (const std::exception& e) {
        mlcritical("exception: %s", e.what());
    }

    return (lib_clickhouse_client_t*)client;
}

void lib_clickhouse_client_execute(lib_clickhouse_client_t* _self, const char* query)
{
    mlassert_self();
    mldebug("execute: %s", query);
    self->Execute(query);
}

void lib_clickhouse_client_select(lib_clickhouse_client_t* _self, const char* query)
{
    mlassert_self();
    mldebug("select: %s", query);
    self->Select(query, [](const Block& block)
        {
            for (size_t row = 0; row < block.GetRowCount(); ++row) {
                for (size_t col = 0; col < block.GetColumnCount(); col++) {
                    std::cout << block.GetColumnName(col) << " " << block[col]->Type()->GetName() << " ";

                    switch (block[col]->Type()->GetCode()) {
                    case Type::Code::Int8:
                        std::cout << int(block[col]->As<ColumnInt8>()->At(row));
                        break;
                    case Type::Code::Int16:
                        std::cout << block[col]->As<ColumnInt16>()->At(row);
                        break;
                    case Type::Code::Int32:
                        std::cout << block[col]->As<ColumnInt32>()->At(row);
                        break;
                    case Type::Code::Int64:
                        std::cout << block[col]->As<ColumnInt64>()->At(row);
                        break;
                    case Type::Code::UInt8:
                        std::cout << unsigned(block[col]->As<ColumnUInt8>()->At(row));
                        break;
                    case Type::Code::UInt16:
                        std::cout << block[col]->As<ColumnUInt16>()->At(row);
                        break;
                    case Type::Code::UInt32:
                        std::cout << block[col]->As<ColumnUInt32>()->At(row);
                        break;
                    case Type::Code::UInt64:
                        std::cout << block[col]->As<ColumnUInt64>()->At(row);
                        break;
                    case Type::Code::String:
                        std::cout << block[col]->As<ColumnString>()->At(row);
                        break;
                    case Type::Code::DateTime64:
                        std::cout << block[col]->As<ColumnDateTime64>()->At(row);
                        break;
                    case Type::Code::IPv4:
                        std::cout << block[col]->As<ColumnIPv4>()->AsString(row);
                        break;
                    case Type::Code::IPv6:
                        std::cout << block[col]->As<ColumnIPv6>()->AsString(row);
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

void lib_clickhouse_client_delete(lib_clickhouse_client_t* _self)
{
    delete self;
}

void lib_clickhouse_client_insert(lib_clickhouse_client_t* _self, const char* tbl, const lib_clickhouse_block_t* block)
{
    mlassert_self();

    self->Insert(tbl, *(Block*)block);
}

}