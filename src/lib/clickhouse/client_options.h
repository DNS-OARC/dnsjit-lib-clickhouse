#ifndef __dnsjit_lib_clickhouse_client_options_h
#define __dnsjit_lib_clickhouse_client_options_h

#ifdef __cplusplus
extern "C" {
#endif

enum clickhouse_client_option {
    CLICKHOUSE_CLIENT_OPTION_HOST,
    CLICKHOUSE_CLIENT_OPTION_PORT,
    CLICKHOUSE_CLIENT_OPTION_USER,
    CLICKHOUSE_CLIENT_OPTION_PASSWORD,
    CLICKHOUSE_CLIENT_OPTION_DEFAULT_DATABASE
};

// dummy struct to typedef clickhouse::ClientOptions
struct clickhouse_client_options {
    void* dummy;
} typedef clickhouse_client_options_t;

clickhouse_client_options_t* clickhouse_client_options_new();
int clickhouse_client_options_set(clickhouse_client_options_t*, enum clickhouse_client_option option, const char*, double);
void clickhouse_client_options_destroy(clickhouse_client_options_t*);

#ifdef __cplusplus
}
#endif

#endif