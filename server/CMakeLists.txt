cmake_minimum_required(VERSION 3.15)

project(BDN)

add_executable(server
    main.cpp
)

target_include_directories(lib PRIVATE ${CMAKE_DIR}/lib)

find_package(Boost 1.79 REQUIRED
    COMPONENTS system date_time)
include_directories(${Boost_INCLUDE_DIR})

target_include_directories(server
    PRIVATE ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}/include)
target_link_libraries(server
    LINK_PRIVATE lib ${Boost_LIBRARIES})

target_compile_features(server PUBLIC cxx_std_17)
set_target_properties(server PROPERTIES CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(server PRIVATE
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(server PRIVATE
        /EHsc
        /W4
        /WX)
endif()