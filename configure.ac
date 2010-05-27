AC_PREREQ(2.57)
AC_INIT(fixedlame, 0.1, avn@daemon.hole.ru)
AM_INIT_AUTOMAKE(foreign)

AC_CONFIG_HEADERS(config.h)

AC_PROG_CC_C99
AM_PROG_LIBTOOL

PKG_CHECK_MODULES(SOX, [sox])

AC_OUTPUT([Makefile src/Makefile src/fixedlame/Makefile src/sox/Makefile fixedlame.pc])
