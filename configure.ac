AC_INIT([mcviewer], [0.0.1], [andy_ball7@hotmail.com], [], [adreamingworld.com])
#AC_CANONICAL_HOST
#AC_CANONICAL_TARGET

AC_CONFIG_AUX_DIR(build-aux)
AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile])

AC_CHECK_HEADERS([stdlib.h])

AC_CHECK_LIB([m], [acos], [], [
	AC_MSG_ERROR([Unable to find acos() function])
	])

PKG_CHECK_MODULES([GLEW], [glew])
PKG_CHECK_MODULES([SDL2], [sdl2])
PKG_CHECK_MODULES([ZLIB], [zlib])

AC_OUTPUT

