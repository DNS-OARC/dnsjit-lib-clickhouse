#include "config.h"

#include <clickhouse/client.h>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

#include <netinet/in.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.column");

// struct _self {
//     enum lib_clickhouse_column_type type;
//     void* column;
// };

// #define self ((struct _self*)_self)

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

    // struct _self* _self = new struct _self();

    // switch (type) {
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT8:
    //     self->column = new ColumnInt8();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT16:
    //     self->column = new ColumnInt16();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT32:
    //     self->column = new ColumnInt32();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT64:
    //     self->column = new ColumnInt64();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT8:
    //     self->column = new ColumnUInt8();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT16:
    //     self->column = new ColumnUInt16();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT32:
    //     self->column = new ColumnUInt32();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
    //     self->column = new ColumnUInt64();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
    //     self->column = new ColumnString();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4:
    //     self->column = new ColumnIPv4();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV6:
    //     self->column = new ColumnIPv6();
    //     break;
    // default:
    //     mlfatal("invalid type");
    // }

    // self->type = type;

    // return (lib_clickhouse_column_t*)_self;
}

lib_clickhouse_column_t* lib_clickhouse_column_new_datetime64(int decimals)
{
    ColumnRef* column = new ColumnRef(std::make_shared<ColumnDateTime64>(decimals));
    // struct _self* _self = new struct _self();

    // self->column = new ColumnDateTime64(decimals);
    // self->type = LIB_CLICKHOUSE_COLUMN_TYPE_DATETIME64;

    // return (lib_clickhouse_column_t*)_self;
    return (lib_clickhouse_column_t*)column;
}

void lib_clickhouse_column_delete(lib_clickhouse_column_t* _self)
{
    mlassert_self();

    // switch (self->type) {
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT8:
    //     delete (ColumnInt8*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT16:
    //     delete (ColumnInt16*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT32:
    //     delete (ColumnInt32*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT64:
    //     delete (ColumnInt64*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT8:
    //     delete (ColumnUInt8*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT16:
    //     delete (ColumnUInt16*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT32:
    //     delete (ColumnUInt32*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
    //     delete (ColumnUInt64*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
    //     delete (ColumnString*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4:
    //     delete (ColumnIPv4*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV6:
    //     delete (ColumnIPv6*)self->column;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_DATETIME64:
    //     delete (ColumnDateTime64*)self->column;
    //     break;
    // }

    delete self;
}

void lib_clickhouse_column_append_number(lib_clickhouse_column_t* _self, const double number)
{
    mlassert_self();

    try {
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

        // switch (self->type) {
        // case LIB_CLICKHOUSE_COLUMN_TYPE_INT8:
        //     ((ColumnInt8*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_INT16:
        //     ((ColumnInt16*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_INT32:
        //     ((ColumnInt32*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_INT64:
        //     ((ColumnInt64*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT8:
        //     ((ColumnUInt8*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT16:
        //     ((ColumnUInt16*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT32:
        //     ((ColumnUInt32*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
        //     ((ColumnUInt64*)self->column)->Append(number);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4:
        //     ((ColumnIPv4*)self->column)->Append(number);
        //     return;
        // default:
        //     mlfatal("invalid type");
        // }
    } catch (const std::exception& e) {
        mlfatal("exception: %s", e.what());
    }

    mlfatal("column not number compatible");
}

void lib_clickhouse_column_append_string(lib_clickhouse_column_t* _self, const char* string)
{
    mlassert_self();
    mlassert(string, "string is nil");

    try {
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

        // switch (self->type) {
        // case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
        //     ((ColumnString*)self->column)->Append(string);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4:
        //     ((ColumnIPv4*)self->column)->Append(string);
        //     return;
        // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV6:
        //     ((ColumnIPv6*)self->column)->Append(string);
        //     return;
        // default:
        //     mlfatal("invalid type");
        // }
    } catch (const std::exception& e) {
        mlfatal("exception: %s", e.what());
    }

    mlfatal("column not string compatible");
}

void lib_clickhouse_column_append_timespec(lib_clickhouse_column_t* _self, core_timespec_t* timespec)
{
    mlassert_self();
    mlassert(timespec, "timespec is nil");

    try {
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

        // switch (self->type) {
        // case LIB_CLICKHOUSE_COLUMN_TYPE_DATETIME64:
        //     ((ColumnDateTime64*)self->column)->Append(timespec->sec * 1000000000 + timespec->nsec);
        //     return;
        // default:
        //     mlfatal("invalid type");
        // }
    } catch (const std::exception& e) {
        mlfatal("exception: %s", e.what());
    }

    mlfatal("column not timespec compatible");
}

void lib_clickhouse_column_append_ipaddr(lib_clickhouse_column_t* _self, uint8_t* addr)
{
    mlassert_self();
    mlassert(addr, "addr is nil");

    try {
        switch ((*self)->Type()->GetCode()) {
        case Type::Code::IPv4:
            if (auto col = (*self)->As<ColumnIPv4>()) {
                col->Append(*(struct in_addr*)addr);
                return;
            }
            break;
        case Type::Code::IPv6:
            if (auto col = (*self)->As<ColumnIPv6>()) {
                col->Append(*(struct in6_addr*)addr);
                return;
            }
            break;
        default:
            break;
        }

        // switch (self->type) {
        // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4: {
        //     struct in_addr a = *(struct in_addr*)addr;
        //     ((ColumnIPv4*)self->column)->Append(a);
        //     return;
        // }
        // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV6: {
        //     struct in6_addr a = *(struct in6_addr*)addr;
        //     ((ColumnIPv6*)self->column)->Append(a);
        //     return;
        // }
        // default:
        //     mlfatal("invalid type");
        // }
    } catch (const std::exception& e) {
        mlfatal("exception: %s", e.what());
    }

    mlfatal("column not ip address compatible");
}

void lib_clickhouse_column_clear(lib_clickhouse_column_t* _self)
{
    mlassert_self();

    // switch (self->type) {
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT8:
    //     ((ColumnInt8*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT16:
    //     ((ColumnInt16*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT32:
    //     ((ColumnInt32*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_INT64:
    //     ((ColumnInt64*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT8:
    //     ((ColumnUInt8*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT16:
    //     ((ColumnUInt16*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT32:
    //     ((ColumnUInt32*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
    //     ((ColumnUInt64*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
    //     ((ColumnString*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV4:
    //     ((ColumnIPv4*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_IPV6:
    //     ((ColumnIPv6*)self->column)->Clear();
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_DATETIME64:
    //     ((ColumnDateTime64*)self->column)->Clear();
    //     break;
    // default:
    //     mlfatal("invalid type");
    // }

    (*self)->Clear();
}

}