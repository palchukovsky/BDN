cmake_minimum_required(VERSION 3.15)

project(BDN)

add_library(lib STATIC
  packet.hpp packet.cpp)

find_package(Boost 1.79 REQUIRED
  COMPONENTS date_time)
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(lib
  LINK_PRIVATE ${Boost_LIBRARIES})

target_compile_features(lib PUBLIC cxx_std_17)
set_target_properties(lib PROPERTIES CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
  CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(lib PRIVATE
    -g
    -Wall
    -Wextra
    -Werror
    -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(lib PRIVATE
    /EHsc
    /W4
    /WX)
endif()