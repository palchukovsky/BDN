cmake_minimum_required(VERSION 3.15)

project(BDN)

include(CMakeLists.txt.config)

configure_file(config.hpp.in ${CMAKE_BINARY_DIR}/include/config.hpp)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*)

add_subdirectory(lib)
add_subdirectory(client)
add_subdirectory(server)