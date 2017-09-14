cmake_minimum_required (VERSION 2.8.11)

add_executable(ex_plot test_plot.cxx)
include_directories(../src/)
link_directories(../src/)

target_link_libraries (ex_plot LINK_PUBLIC  cairo fftw3 plotty ${GTKMM_LIBRARIES})
target_include_directories(ex_plot PUBLIC /usr/include/eigen3/)

set_target_properties( ex_plot
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)