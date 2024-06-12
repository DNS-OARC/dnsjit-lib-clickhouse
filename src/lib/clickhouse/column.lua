local ffi = require("ffi")
local C = ffi.C

local Column = {}

-- Create a new Clickhouse Column.
function Column.new(type)
    local self = {
        obj = C.lib_clickhouse_column_new(type),
    }
    ffi.gc(self.obj, C.lib_clickhouse_column_delete)
    return setmetatable(self, { __index = Column })
end

function Column.new_uint64()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_UINT64")
end

return Column
