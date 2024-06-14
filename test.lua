local log = require("dnsjit.core.log")
log.enable("all")

--package.path = package.path .. ";./src/?.lua"

--local ch = require("dnsjit.lib.clickhouse").new()

-- package.path = package.path .. ";/home/jerry/dnsjit/build/root/usr/local/share/lua/5.1/?.lua"
-- print(package.path)
-- package.cpath = package.cpath .. ";/home/jerry/dnsjit/build/root/usr/local/lib/lua/5.1/?.so"
-- print(package.cpath)
local clickhouse = require("dnsjit.lib.clickhouse").new()

local opts = clickhouse.ClientOptions.new()

opts:set_host("172.17.0.1")
opts:set_port(8000)

local cli = clickhouse.Client.new(opts)

--cli:execute("CREATE TEMPORARY TABLE IF NOT EXISTS test_client (id UInt64, name String)")
-- local id = clickhouse.Column.new_uint64()
-- id:append(1)
-- id:append(7)
-- local name = clickhouse.Column.new_string()
-- name:append("one")
-- name:append("seven")
-- local block = clickhouse.Block.new()
-- block:append_column("id", id)
-- block:append_column("name", name)
--cli:insert("test_client", block)

cli:execute("CREATE TEMPORARY TABLE IF NOT EXISTS test_client (ts DateTime64(9), dst IPv6, src IPv6, id UInt16, flags UInt16, opcode UInt8, rcode UInt8, qtype UInt16, qclass UInt16, qname String) engine = MergeTree() order by (ts)")

local block = clickhouse.Block.new()

local ts = clickhouse.Column.new_datetime64(9) --DateTime64,
require("dnsjit.core.timespec_h")
local stamp = require("ffi").new("core_timespec_t")
stamp.sec = 123456789
stamp.nsec = 123456789
ts:append(stamp)
block:append_column("ts", ts)

local dst = clickhouse.Column.new_ipv6() --IPv6,
dst:append("2600::1")
block:append_column("dst", dst)

local src = clickhouse.Column.new_ipv6() --IPv6,
src:append("42::1")
block:append_column("src", src)

local id = clickhouse.Column.new_uint16() --UInt16,
id:append(123456)
block:append_column("id", id)

local flags = clickhouse.Column.new_uint16() --UInt16,
flags:append(0x1234)
block:append_column("flags", flags)

local opcode = clickhouse.Column.new_uint8() --UInt8,
opcode:append(1)
block:append_column("opcode", opcode)

local rcode = clickhouse.Column.new_uint8() --UInt8,
rcode:append(2)
block:append_column("rcode", rcode)

local qtype = clickhouse.Column.new_uint16() --UInt16,
qtype:append(3)
block:append_column("qtype", qtype)

local qclass = clickhouse.Column.new_uint16() --UInt16,
qclass:append(4)
block:append_column("qclass", qclass)

local qname = clickhouse.Column.new_string() --String,
qname:append("test.example.com")
block:append_column("qname", qname)

cli:insert("test_client", block)

-- cli:execute("INSERT INTO test_client (id, name) VALUES (1, 'one')")
cli:select("SELECT * FROM test_client")
cli:execute("DROP TEMPORARY TABLE test_client")
