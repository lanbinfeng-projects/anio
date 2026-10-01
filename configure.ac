AC_INIT([anio], [1.0-rc1], [])
AM_INIT_AUTOMAKE
LT_INIT

AC_PROG_CXX

AC_ARG_ENABLE([samples],
	      [AS_HELP_STRING([--enable-samples], [enable build samples])],
	      [build_samples=$enableval],
	      [build_samples=no])
AM_CONDITIONAL([BUILD_SAMPLES], [test "x$build_samples" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
