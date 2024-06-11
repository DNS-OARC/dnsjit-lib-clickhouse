module(...,package.seeall)

require("dnsjit.core.log")

--local loader = require("dnsjit.core.loader")
--loader.load("dnsjit-lib-clickhouse/clickhouse")
--loader.load("./src/.lib/clickhouse.so")

local ffi = require("ffi")
ffi.load("./src/.libs/clickhouse.so", true)
ffi.cdef[[
typedef struct lib_clickhouse {
    core_log_t _log;

    void* options;
    void* client;
} lib_clickhouse_t;

core_log_t* lib_clickhouse_log();
void lib_clickhouse_init(lib_clickhouse_t*);
int lib_clickhouse_set_host(lib_clickhouse_t*, const char*);
int lib_clickhouse_set_port(lib_clickhouse_t*, double);
void lib_clickhouse_connect(lib_clickhouse_t*);
void lib_clickhouse_execute(lib_clickhouse_t*, const char*);
void lib_clickhouse_select(lib_clickhouse_t*, const char*);
void lib_clickhouse_destroy(lib_clickhouse_t*);
]]
local C = ffi.C

local t_name = "lib_clickhouse_t"
local lib_clickhouse_t = ffi.typeof(t_name)
local Clickhouse = {}

-- Create a new Clickhouse filter.
function Clickhouse.new()
    local self = {
        obj = lib_clickhouse_t(),
    }
    C.lib_clickhouse_init(self.obj)
    ffi.gc(self.obj, C.lib_clickhouse_destroy)
    return setmetatable(self, { __index = Clickhouse })
end

-- Return the Log object to control logging of this instance or module.
function Clickhouse:log()
    if self == nil then
        return C.lib_clickhouse_log()
    end
    return self.obj._log
end

-- TODO
function Clickhouse:set_host(host)
    return C.lib_clickhouse_set_host(self.obj, host)
end

-- TODO
function Clickhouse:set_port(port)
    return C.lib_clickhouse_set_port(self.obj, port)
end

-- TODO
function Clickhouse:connect()
    C.lib_clickhouse_connect(self.obj)
end

-- TODO
function Clickhouse:execute(query)
    C.lib_clickhouse_execute(self.obj, query)
end

-- TODO
function Clickhouse:select(query)
    C.lib_clickhouse_select(self.obj, query)
end

return Clickhouse
