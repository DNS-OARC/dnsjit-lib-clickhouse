local ffi = require("ffi")
local C = ffi.C

local ClientOptions = {}

-- Create a new Clickhouse ClientOptions.
function ClientOptions.new()
    local self = {
        obj = C.lib_clickhouse_client_options_new(),
    }
    ffi.gc(self.obj, C.lib_clickhouse_client_options_delete)
    return setmetatable(self, { __index = ClientOptions })
end

-- TODO
function ClientOptions:set_host(host)
    return C.lib_clickhouse_client_options_set(self.obj, "LIB_CLICKHOUSE_CLIENT_OPTION_HOST", host, 0)
end

-- TODO
function ClientOptions:set_port(port)
    return C.lib_clickhouse_client_options_set(self.obj, "LIB_CLICKHOUSE_CLIENT_OPTION_PORT", nil, port)
end

return ClientOptions
