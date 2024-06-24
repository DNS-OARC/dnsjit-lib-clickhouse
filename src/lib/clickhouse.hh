// lua:require("dnsjit.core.log")
// lua:require("dnsjit.core.timespec")

/* COLUMN */

enum lib_clickhouse_column_type {
    LIB_CLICKHOUSE_COLUMN_TYPE_INT8,
    LIB_CLICKHOUSE_COLUMN_TYPE_INT16,
    LIB_CLICKHOUSE_COLUMN_TYPE_INT32,
    LIB_CLICKHOUSE_COLUMN_TYPE_INT64,
    LIB_CLICKHOUSE_COLUMN_TYPE_UINT8,
    LIB_CLICKHOUSE_COLUMN_TYPE_UINT16,
    LIB_CLICKHOUSE_COLUMN_TYPE_UINT32,
    LIB_CLICKHOUSE_COLUMN_TYPE_UINT64,
    LIB_CLICKHOUSE_COLUMN_TYPE_STRING,
    LIB_CLICKHOUSE_COLUMN_TYPE_DATETIME64,
    LIB_CLICKHOUSE_COLUMN_TYPE_IPV4,
    LIB_CLICKHOUSE_COLUMN_TYPE_IPV6
};

typedef struct lib_clickhouse_column lib_clickhouse_column_t;

lib_clickhouse_column_t* lib_clickhouse_column_new(enum lib_clickhouse_column_type);
lib_clickhouse_column_t* lib_clickhouse_column_new_datetime64(int);
void lib_clickhouse_column_delete(lib_clickhouse_column_t*);
void lib_clickhouse_column_append(lib_clickhouse_column_t*);
void lib_clickhouse_column_append_number(lib_clickhouse_column_t*, const double);
void lib_clickhouse_column_append_string(lib_clickhouse_column_t*, const char*);
void lib_clickhouse_column_append_timespec(lib_clickhouse_column_t*, core_timespec_t*);
void lib_clickhouse_column_append_ipaddr(lib_clickhouse_column_t*, uint8_t*);
void lib_clickhouse_column_clear(lib_clickhouse_column_t*);


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
void lib_clickhouse_client_insert(lib_clickhouse_client_t*, const char*, const lib_clickhouse_block_t*);


/* CLICKHOUSE */

typedef struct lib_clickhouse {
    core_log_t _log;
} lib_clickhouse_t;

core_log_t* lib_clickhouse_log();
void lib_clickhouse_init(lib_clickhouse_t*);
void lib_clickhouse_destroy(lib_clickhouse_t*);
