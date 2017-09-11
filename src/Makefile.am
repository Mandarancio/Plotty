lib_LTLIBRARIES = libplotty-@API_VERSION@.la

libplotty_@API_VERSION@_la_SOURCES = \
	plotty.cxx \
	plotty-version.h \
	math.cxx \
	images.cxx \
	fft.cxx \
	$(NULL)

libplotty_@API_VERSION@_la_CXXFLAGS = \
	-Isrc/ -I/usr/include/eigen3/ `pkg-config --cflags gtkmm-3.0`\
	$(PLOTTY_CFLAGS) \
	$(NULL)

libplotty_@API_VERSION@_la_LIBADD = \
	$(PLOTTY_LIBS) \
	$(NULL)

libplotty_@API_VERSION@_la_LDFLAGS = \
	-shared -fPIC -g \
	-lcairo `pkg-config --libs gtkmm-3.0` -lfftw3 \
	$(WARN_LDFLAGS) \
	$(NULL)

-include $(top_srcdir)/git.mk
