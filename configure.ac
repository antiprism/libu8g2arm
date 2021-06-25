
AC_PREREQ([2.69])
AC_INIT([libu8g2arm], [0.01], [adrian@antiprism.com])
AC_CONFIG_SRCDIR([src/port/spi.c])
AC_CONFIG_AUX_DIR([build_aux])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.9 foreign subdir-objects])
AM_PROG_AR

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX(11)

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset strncasecmp])

AC_CONFIG_FILES([ Makefile
                  src/Makefile
                  examples/Makefile
                  ])

AC_OUTPUT
