local log = require("dnsjit.core.log")
log.enable("all")

package.path = package.path .. ";./src/?.lua"

--local ch = require("dnsjit.lib.clickhouse").new()
local clickhouse = require("dnsjit.lib.clickhouse").new()

local opts = clickhouse.ClientOptions.new()

opts:set_host("172.17.0.1")
opts:set_port(8000)

local cli = clickhouse.Client.new(opts)

cli:execute("CREATE TEMPORARY TABLE IF NOT EXISTS test_client (id UInt64, name String)")

-- local id = require("dnsjit.lib.clickhouse.column.uint64").new()
-- id:append(1)
-- id:append(7)
-- local name = require("dnsjit.lib.clickhouse.column.string").new()
-- name:append("one")
-- name:append("seven")
-- local block = require("dnsjit.lib.clickhouse.block").new()
-- block:append_column("id", id)
-- block:append_column("name", name)
-- ch:insert("test_client", block)

cli:execute("INSERT INTO test_client (id, name) VALUES (1, 'one')")
cli:select("SELECT * FROM test_client")
cli:execute("DROP TEMPORARY TABLE test_client")
