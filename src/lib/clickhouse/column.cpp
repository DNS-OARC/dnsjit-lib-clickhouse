#include "config.h"

#include <clickhouse/client.h>

using namespace clickhouse;

extern "C" {

#include "../clickhouse.h"

#include <dnsjit/core/assert.h>

static core_log_t       _log      = LOG_T_INIT("dnsjit.lib.clickhouse.column");

// struct __container {
//     enum lib_clickhouse_column_type type;
//     ColumnUInt64* uint64;
//     ColumnString* string;
// };

//#define self ((struct __container*)_self)
#define self ((ColumnRef*)_self)

lib_clickhouse_column_t* lib_clickhouse_column_new(enum lib_clickhouse_column_type type)
{
    // struct __container* _self = new struct __container();

    ColumnRef* column;

    switch (type) {
    case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
        // self->uint64 = new ColumnUInt64();
        column = new ColumnRef(std::make_shared<ColumnUInt64>());
        break;
    case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
        // self->string = new ColumnString();
        column = new ColumnRef(std::make_shared<ColumnString>());
        break;
    default:
        mlfatal("invalid type");
    }

    // self->type = type;

    // return (lib_clickhouse_column_t*)_self;
    return (lib_clickhouse_column_t*)column;
}

void lib_clickhouse_column_delete(lib_clickhouse_column_t* _self)
{
    // switch (self->type) {
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
    //     delete self->uint64;
    //     break;
    // case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
    //     delete self->string;
    //     break;
    // }

    delete self;
}

void lib_clickhouse_column_append_number(lib_clickhouse_column_t* _self, const double number)
{
    mlassert_self();

    if (auto col = (*self)->As<ColumnUInt64>()) {
        col->Append(number);
    } else {
        mlfatal("column not a number");
    }

    // switch (self->type) {
    // case LIB_CLICKHOUSE_COLUMN_TYPE_UINT64:
    //     self->uint64->Append(number);
    //     break;
    // default:
    //     mlfatal("column not a number");
    // }
}

void lib_clickhouse_column_append_string(lib_clickhouse_column_t* _self, const char* string)
{
    mlassert_self();

    if (auto col = (*self)->As<ColumnString>()) {
        col->Append(string);
    } else {
        mlfatal("column not a string");
    }

    // switch (self->type) {
    // case LIB_CLICKHOUSE_COLUMN_TYPE_STRING:
    //     self->string->Append(string);
    //     break;
    // default:
    //     mlfatal("column not a string");
    // }
}

}