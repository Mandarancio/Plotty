cmake_minimum_required (VERSION 2.8.11)
add_library (plotty SHARED plotty.cxx math.cxx images.cxx fft.cxx)
target_link_libraries (plotty LINK_PUBLIC cairo fftw3)
target_include_directories(plotty PUBLIC /usr/include/eigen3/)

set_target_properties( plotty
PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)