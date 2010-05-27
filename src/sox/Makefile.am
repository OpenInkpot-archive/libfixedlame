soxlibdir = ${libdir}/sox
soxlib_LTLIBRARIES = sox_fmt_fixedpoint_mp3.la

AM_CFLAGS = -I${srcdir}/../fixedlame @SOX_CFLAGS@

sox_fmt_fixedpoint_mp3_la_SOURCES = plugin.c
sox_fmt_fixedpoint_mp3_la_LDFLAGS = -module -shared -avoid-version @SOX_LIBS@
sox_fmt_fixedpoint_mp3_la_LIBADD = ../fixedlame/libfixedlame.la
