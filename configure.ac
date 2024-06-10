AC_PREREQ(2.61)
AC_INIT([dnsjit-lib-clickhouse], [0.1.0],,)
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_HEADER([src/config.h])
AC_CONFIG_COMMANDS([clickhouse-cpp], [cmake -S "$srcdir/clickhouse-cpp" -B clickhouse-cpp -D WITH_OPENSSL=ON -D WITH_SYSTEM_LZ4=ON -D WITH_SYSTEM_ZSTD=ON -D BUILD_SHARED_LIBS=ON])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_CANONICAL_HOST
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT([disable-static])

# Check for dnsjit binaries and development files
DNSJIT_ROOT=
AC_ARG_WITH([dnsjit], [AS_HELP_STRING([--with-dnsjit=PATH], [Use PATH when checking for dnsjit binaries and development files])], [
  AC_PATH_PROG([DNSJIT],[dnsjit],,[$withval/bin])
  AS_VAR_APPEND(CFLAGS, [" -I$withval/include"])
  DNSJIT_ROOT="$withval"
], [
  AC_PATH_PROG([DNSJIT],[dnsjit])
])
AC_CHECK_HEADER([dnsjit/version.h],, [AC_MSG_ERROR([dnsjit development headers not found])])
AC_SUBST([DNSJIT_ROOT])
AS_IF([test "x$ac_cv_path_DNSJIT" = "x"], [
  AC_MSG_ERROR([dnsjit was not found])
])
AC_MSG_CHECKING([for dnsjit >= 1.3.0])
AS_IF(["$DNSJIT" "$srcdir/dnsjit_version.lua" 1 3 0], [
  AC_MSG_RESULT([yes])
], [
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([dnsjit version does not meet the requirements])
])

# Output Makefiles
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
