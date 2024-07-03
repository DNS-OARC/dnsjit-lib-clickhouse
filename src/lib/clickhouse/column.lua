local ffi = require("ffi")
local C = ffi.C

local Column = {}

-- Create a new Clickhouse Column.
function Column.new(type)
    local self = {
        obj = C.lib_clickhouse_column_new(type)
    }
    ffi.gc(self.obj, C.lib_clickhouse_column_delete)
    return setmetatable(self, { __index = Column })
end

function Column.new_int8()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_INT8")
end

function Column.new_int16()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_INT16")
end

function Column.new_int32()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_INT32")
end

function Column.new_int64()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_INT64")
end

function Column.new_uint8()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_UINT8")
end

function Column.new_uint16()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_UINT16")
end

function Column.new_uint32()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_UINT32")
end

function Column.new_uint64()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_UINT64")
end

function Column.new_string()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_STRING")
end

function Column.new_datetime64(decimals)
    local self = {
        obj = C.lib_clickhouse_column_new_datetime64(decimals)
    }
    ffi.gc(self.obj, C.lib_clickhouse_column_delete)
    return setmetatable(self, { __index = Column })
end

function Column.new_ipv4()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_IPV4")
end

function Column.new_ipv6()
    return Column.new("LIB_CLICKHOUSE_COLUMN_TYPE_IPV6")
end

function Column:append(value)
    local t = type(value)
    if t == "number" then
        C.lib_clickhouse_column_append_number(self.obj, value)
    elseif t == "string" then
        C.lib_clickhouse_column_append_string(self.obj, value)
    elseif t == "cdata" then
        if ffi.istype("core_timespec_t", value) == true then
            C.lib_clickhouse_column_append_timespec(self.obj, value)
        else
            -- try number for all (u)int8/16/32/64_t's
            C.lib_clickhouse_column_append_number(self.obj, value)
        end
    end
end

function Column:append_number(value)
    C.lib_clickhouse_column_append_number(self.obj, value)
end

function Column:append_string(value)
    C.lib_clickhouse_column_append_string(self.obj, value)
end

function Column:append_timespec(value)
    C.lib_clickhouse_column_append_timespec(self.obj, value)
end

-- todo: doc value size up to caller to match column
function Column:append_ipaddr(ipv, value)
    C.lib_clickhouse_column_append_ipaddr(self.obj, ipv, value)
end

function Column:clear()
    C.lib_clickhouse_column_clear(self.obj)
end

return Column
