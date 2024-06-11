#ifndef __dnsjit_lib_clickhouse_client_options_h
#define __dnsjit_lib_clickhouse_client_options_h

#ifdef __cplusplus
extern "C" {
#endif

// dummy struct to typedef clickhouse::ClientOptions
struct clickhouse_client_options {
    void* dummy;
} typedef clickhouse_client_options_t;

clickhouse_client_options_t* clickhouse_client_options_new();
void clickhouse_client_options_destroy(clickhouse_client_options_t*);

#ifdef __cplusplus
}
#endif

#endif