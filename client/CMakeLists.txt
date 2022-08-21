cmake_minimum_required(VERSION 3.15)

project(BDN)

add_executable(client
    main.cpp
    fwd.hpp
    client.hpp
    network_client.hpp network_client.cpp
    source.hpp source.cpp
    task.hpp task.cpp)

target_include_directories(lib PRIVATE ${CMAKE_DIR}/lib)

find_package(Boost 1.79 REQUIRED
    COMPONENTS system date_time)
include_directories(${Boost_INCLUDE_DIR})

target_include_directories(client
    PRIVATE ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}/include)
target_link_libraries(client
    LINK_PRIVATE lib ${Boost_LIBRARIES})

target_compile_features(client PUBLIC cxx_std_17)
set_target_properties(client PROPERTIES CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(client PRIVATE
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(client PRIVATE
        /EHsc
        /W4
        /WX)
endif()