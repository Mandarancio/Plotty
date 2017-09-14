cmake_minimum_required (VERSION 2.8.11)

add_executable(ex_plot test_plot.cxx)
add_executable(ex_fft test_fft.cxx)
add_executable(ex_img test_img.cxx)
add_executable(benchmark benchmark.cxx)

include_directories(../src/ /usr/include/eigen3/)
link_directories(../src/)

target_link_libraries (ex_plot cairo fftw3 plotty ${GTKMM_LIBRARIES})
target_link_libraries (ex_fft cairo fftw3 plotty ${GTKMM_LIBRARIES})
target_link_libraries (ex_img cairo fftw3 plotty ${GTKMM_LIBRARIES})
target_link_libraries (benchmark cairo fftw3 plotty ${GTKMM_LIBRARIES})


set_target_properties( ex_plot
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties( ex_fft
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties( ex_img
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties( benchmark
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)