MAINTAINERCLEANFILES = $(srcdir)/Makefile.in \
  $(srcdir)/configure

SUBDIRS = clickhouse-cpp src

dist_doc_DATA = README.md

EXTRA_DIST = dnsjit_version.lua test.lua

test:
	$(DNSJIT) $(srcdir)/test.lua
