local log = require("dnsjit.core.log")
log.enable("all")

local clickhouse = require("dnsjit.lib.clickhouse").new()

clickhouse:connect()