local log = require("dnsjit.core.log")
log.enable("all")

local ch = require("dnsjit.lib.clickhouse").new()

ch:set_host("172.17.0.1")
ch:set_port(8000)
ch:connect()

ch:execute("CREATE TEMPORARY TABLE IF NOT EXISTS test_client (id UInt64, name String)")

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

ch:execute("INSERT INTO test_client (id, name) VALUES (1, 'one')")
ch:select("SELECT * FROM test_client")
ch:execute("DROP TEMPORARY TABLE test_client")
