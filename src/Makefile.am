MAINTAINERCLEANFILES = $(srcdir)/Makefile.in
CLEANFILES =

AM_CFLAGS = -Werror=attributes \
  -I$(srcdir) \
  -I$(top_srcdir)

AM_CXXFLAGS = -Werror=attributes \
  -I$(srcdir) \
  -I$(top_srcdir) \
  -I$(top_srcdir)/clickhouse-cpp \
  -I$(top_srcdir)/clickhouse-cpp/contrib/absl \
  -I$(top_srcdir)/clickhouse-cpp/contrib/cityhash \
  -I$(top_srcdir)/clickhouse-cpp/contrib/lz4 \
  -I$(top_srcdir)/clickhouse-cpp/contrib/zstd

pkglibdir = $(libdir)/lua/5.1/$(PACKAGE)
pkglib_LTLIBRARIES = clickhouse.la
clickhouse_la_SOURCES = lib/clickhouse.c lib/clickhouse/client.cpp \
  lib/clickhouse/client_options.cpp lib/clickhouse/block.cpp \
  lib/clickhouse/column.cpp
clickhouse_la_LDFLAGS = -Wl,-E -module -avoid-version -shared -L../clickhouse-cpp/clickhouse -lclickhouse-cpp-lib

clickhouselibdir = $(datadir)/lua/5.1/dnsjit/lib
dist_clickhouselib_DATA = lib/clickhouse.lua lib/clickhouse_h.lua

clickhouselib2dir = $(datadir)/lua/5.1/dnsjit/lib/clickhouse
dist_clickhouselib2_DATA = lib/clickhouse/client.lua \
  lib/clickhouse/client_options.lua lib/clickhouse/block.lua \
  lib/clickhouse/column.lua

BUILT_SOURCES = lib/clickhouse_h.lua

lib/clickhouse_h.lua: lib/clickhouse.hh
	@echo 'module(...,package.seeall);' > "$@"
	@cat "$<" | grep '^// *lua:' | sed 's%^// *lua:%%' >> "$@"
	@echo 'require("ffi").cdef[[' >> "$@"
	@cat "$<" | grep -v '^#' >> "$@"
	@echo ']]' >> "$@"
