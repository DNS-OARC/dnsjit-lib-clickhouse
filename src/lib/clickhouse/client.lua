local ffi = require("ffi")
local C = ffi.C

local Client = {}

-- Create a new Clickhouse Client.
function Client.new(options)
    if ffi.istype("lib_clickhouse_client_options_t", options.obj) == false then
        error("invalid options")
    end
    local self = {
        obj = C.lib_clickhouse_client_new(options.obj),
    }
    ffi.gc(self.obj, C.lib_clickhouse_client_delete)
    return setmetatable(self, { __index = Client })
end

-- TODO
function Client:execute(query)
    C.lib_clickhouse_client_execute(self.obj, query)
end

-- TODO
function Client:select(query)
    C.lib_clickhouse_client_select(self.obj, query)
end

return Client
