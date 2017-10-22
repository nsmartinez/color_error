cmake_minimum_required (VERSION 2.6)
project (color_error)

set(CMAKE_CXX_FLAGS "--std=c++11 -O3")


include_directories ("${PROJECT_SOURCE_DIR}/src")

file(GLOB COLOR_ERROR_LIB_SOURCES "src/color_error/*.cc")

add_library(color_error_lib ${COLOR_ERROR_LIB_SOURCES})

add_executable(color_error ${PROJECT_SOURCE_DIR}/src/color_error.cc)
target_link_libraries(color_error color_error_lib)

install(TARGETS color_error DESTINATION bin)
