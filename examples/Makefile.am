-include $(top_srcdir)/git.mk

bin_PROGRAMS = \
	test_fft \
	test_plot \
	test_img

test_plot_SOURCES = test_plot.cxx

test_plot_LDFLAGS = \
	-lplotty-0 -L../src/\
	-lcairo `pkg-config --libs gtkmm-3.0` -lfftw3

test_plot_CXXFLAGS = \
	-I/usr/include/eigen3/ `pkg-config --cflags gtkmm-3.0`\
	$(NULL)


test_fft_SOURCES = test_fft.cxx

test_fft_LDFLAGS = \
	-lplotty-0 -L../src/\
	-lcairo `pkg-config --libs gtkmm-3.0` -lfftw3

test_fft_CXXFLAGS = \
	-I/usr/include/eigen3/ `pkg-config --cflags gtkmm-3.0`\
	$(NULL)

test_img_SOURCES = test_img.cxx

test_img_LDFLAGS = \
	-lplotty-0 -L../src/\
	-lcairo `pkg-config --libs gtkmm-3.0` -lfftw3

test_img_CXXFLAGS = \
	-I/usr/include/eigen3/ `pkg-config --cflags gtkmm-3.0`\
	$(NULL)
