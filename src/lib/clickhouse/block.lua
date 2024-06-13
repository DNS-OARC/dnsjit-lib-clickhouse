local ffi = require("ffi")
local C = ffi.C

local Block = {}

-- Create a new Clickhouse Block.
function Block.new()
    local self = {
        obj = C.lib_clickhouse_block_new(),
    }
    ffi.gc(self.obj, C.lib_clickhouse_block_delete)
    return setmetatable(self, { __index = Block })
end

-- TODO
function Block:append_column(name, column)
    C.lib_clickhouse_block_append_column(self.obj, name, column.obj)
end

return Block
