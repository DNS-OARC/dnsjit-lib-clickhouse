module(...,package.seeall)

local loader = require("dnsjit.core.loader")
loader.load("dnsjit-lib-clickhouse/clickhouse")

local ffi = require("ffi")
require("dnsjit.lib.clickhouse_h")
local C = ffi.C

local t_name = "lib_clickhouse_t"
local lib_clickhouse_t = ffi.typeof(t_name)
local Clickhouse = {}

local Column = require("dnsjit.lib.clickhouse.column")
local Block = require("dnsjit.lib.clickhouse.block")
local ClientOptions = require("dnsjit.lib.clickhouse.client_options")
local Client = require("dnsjit.lib.clickhouse.client")

-- Create a new Clickhouse client.
function Clickhouse.new()
    local self = {
        obj = lib_clickhouse_t(),
        Column = Column,
        Block = Block,
        ClientOptions = ClientOptions,
        Client = Client
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

return Clickhouse
