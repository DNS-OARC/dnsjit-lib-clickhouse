local log = require("dnsjit.core.log")
log.enable("all")

local ch = require("dnsjit.lib.clickhouse").new()

ch:set_host("172.17.0.1")
ch:set_port(8000)
ch:connect()

ch:execute("CREATE TEMPORARY TABLE IF NOT EXISTS test_client (something UInt64)")
ch:execute("INSERT INTO test_client VALUES (1)")
ch:select("SELECT * FROM test_client")
ch:execute("DROP TEMPORARY TABLE test_client")
