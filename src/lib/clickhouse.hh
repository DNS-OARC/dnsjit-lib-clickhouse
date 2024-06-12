// lua:require("dnsjit.core.log")

/* COLUMN */

typedef struct lib_clickhouse_column lib_clickhouse_column_t;


/* BLOCK */

typedef struct lib_clickhouse_block lib_clickhouse_block_t;

lib_clickhouse_block_t* lib_clickhouse_block_new();
void lib_clickhouse_block_delete(lib_clickhouse_block_t*);
void lib_clickhouse_block_append_column(lib_clickhouse_block_t*, const char*, lib_clickhouse_column_t*);


/* OPTIONS */

enum lib_clickhouse_client_option {
    LIB_CLICKHOUSE_CLIENT_OPTION_HOST,
    LIB_CLICKHOUSE_CLIENT_OPTION_PORT,
    LIB_CLICKHOUSE_CLIENT_OPTION_USER,
    LIB_CLICKHOUSE_CLIENT_OPTION_PASSWORD,
    LIB_CLICKHOUSE_CLIENT_OPTION_DEFAULT_DATABASE
};

typedef struct lib_clickhouse_client_options lib_clickhouse_client_options_t;

lib_clickhouse_client_options_t* lib_clickhouse_client_options_new();
void lib_clickhouse_client_options_delete(lib_clickhouse_client_options_t*);
int lib_clickhouse_client_options_set(lib_clickhouse_client_options_t*, enum lib_clickhouse_client_option, const char*, double);


/* CLIENT */

typedef struct lib_clickhouse_client lib_clickhouse_client_t;

lib_clickhouse_client_t* lib_clickhouse_client_new(const lib_clickhouse_client_options_t*);
void lib_clickhouse_client_execute(lib_clickhouse_client_t*, const char*);
void lib_clickhouse_client_select(lib_clickhouse_client_t*, const char*);
void lib_clickhouse_client_delete(lib_clickhouse_client_t*);


/* CLICKHOUSE */

typedef struct lib_clickhouse {
    core_log_t _log;
} lib_clickhouse_t;

core_log_t* lib_clickhouse_log();
void lib_clickhouse_init(lib_clickhouse_t*);
void lib_clickhouse_destroy(lib_clickhouse_t*);
