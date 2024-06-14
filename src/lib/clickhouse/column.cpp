#include "config.h"

#include <clickhouse/client.h>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.column");

#define self ((ColumnRef*)_self)

lib_clickhouse_column_t* lib_clickhouse_column_new(enum lib_clickhouse_column_type type)
{
    ColumnRef* column;

    switch (type) {
    case LIB_CLICKHOUSE_COLUMN_TYPE_INT8:
        column = new ColumnRef(std::make_shared<ColumnInt8>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_INT16:
        column = new ColumnRef(std::make_shared<ColumnInt16>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_INT32:
        column = new ColumnRef(std::make_shared<ColumnInt32>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_INT64:
        column = new ColumnRef(std::make_shared<ColumnInt64>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_UINT8:
        column = new ColumnRef(std::make_shared<ColumnUInt8>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_UINT16:
        column = new ColumnRef(std::make_shared<ColumnUInt16>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_UINT32:
        column = new ColumnRef(std::make_shared<ColumnUInt32>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
        column = new ColumnRef(std::make_shared<ColumnUInt64>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
        column = new ColumnRef(std::make_shared<ColumnString>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4:
        column = new ColumnRef(std::make_shared<ColumnIPv4>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_IPV6:
        column = new ColumnRef(std::make_shared<ColumnIPv6>());
        break;
    default:
        mlfatal("invalid type");
    }

    return (lib_clickhouse_column_t*)column;
}

lib_clickhouse_column_t* lib_clickhouse_column_new_datetime64(int decimals)
{
    ColumnRef* column = new ColumnRef(std::make_shared<ColumnDateTime64>(decimals));

    return (lib_clickhouse_column_t*)column;
}

void lib_clickhouse_column_delete(lib_clickhouse_column_t* _self)
{
    delete self;
}

void lib_clickhouse_column_append_number(lib_clickhouse_column_t* _self, const double number)
{
    mlassert_self();

    switch ((*self)->Type()->GetCode()) {
    case Type::Code::Int8:
        if (auto col = (*self)->As<ColumnInt8>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::Int16:
        if (auto col = (*self)->As<ColumnInt16>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::Int32:
        if (auto col = (*self)->As<ColumnInt32>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::Int64:
        if (auto col = (*self)->As<ColumnInt64>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::UInt8:
        if (auto col = (*self)->As<ColumnUInt8>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::UInt16:
        if (auto col = (*self)->As<ColumnUInt16>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::UInt32:
        if (auto col = (*self)->As<ColumnUInt32>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::UInt64:
        if (auto col = (*self)->As<ColumnUInt64>()) {
            col->Append(number);
            return;
        }
        break;
    case Type::Code::IPv4:
        if (auto col = (*self)->As<ColumnIPv4>()) {
            col->Append(number);
            return;
        }
        break;
    default:
        break;
    }

    mlfatal("column not number compatible");
}

void lib_clickhouse_column_append_string(lib_clickhouse_column_t* _self, const char* string)
{
    mlassert_self();
    mlassert(string, "string is nil");

    switch ((*self)->Type()->GetCode()) {
    case Type::Code::String:
        if (auto col = (*self)->As<ColumnString>()) {
            col->Append(string);
            return;
        }
        break;
    case Type::Code::IPv4:
        if (auto col = (*self)->As<ColumnIPv4>()) {
            col->Append(string);
            return;
        }
        break;
    case Type::Code::IPv6:
        if (auto col = (*self)->As<ColumnIPv6>()) {
            col->Append(string);
            return;
        }
        break;
    default:
        break;
    }

    mlfatal("column not string compatible");
}

void lib_clickhouse_column_append_timespec(lib_clickhouse_column_t* _self, core_timespec_t* timespec)
{
    mlassert_self();
    mlassert(timespec, "timespec is nil");

    switch ((*self)->Type()->GetCode()) {
    case Type::Code::DateTime64:
        if (auto col = (*self)->As<ColumnDateTime64>()) {
            col->Append(timespec->sec * 1000000000 + timespec->nsec);
            return;
        }
        break;
    default:
        break;
    }

    mlfatal("column not timespec compatible");
}

}