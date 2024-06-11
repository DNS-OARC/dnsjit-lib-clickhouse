#include "client_options.h"

#ifndef __dnsjit_lib_clickhouse_client_h
#define __dnsjit_lib_clickhouse_client_h

#ifdef __cplusplus
extern "C" {
#endif

// dummy struct to typedef clickhouse::Client
struct clickhouse_client {
    void* dummy;
} typedef clickhouse_client_t;

clickhouse_client_t* clickhouse_client_new(const clickhouse_client_options_t*);
void clickhouse_client_execute(clickhouse_client_t*, const char*);
void clickhouse_client_select(clickhouse_client_t*, const char*);
void clickhouse_client_destroy(clickhouse_client_t*);

#ifdef __cplusplus
}
#endif

#endif
