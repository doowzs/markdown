cmake_minimum_required(VERSION 3.13)
project(markdown)

file(GLOB CMAKE_CXX_SOURCES src/*.cpp)
file(GLOB CMAKE_CXX_HEADERS src/headers/*.h)
set(CMAKE_CXX_INCLUDE_PATH src/headers)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    list(APPEND CMAKE_CXX_COMPILE_FLAGS -Wall -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    list(APPEND CMAKE_CXX_COMPILE_FLAGS -Wall -Werror)
endif()

add_executable(markdown ${CMAKE_CXX_HEADERS} ${CMAKE_CXX_SOURCES})
target_include_directories(markdown PRIVATE ${CMAKE_CXX_INCLUDE_PATH})
target_compile_options(markdown PRIVATE ${CMAKE_CXX_COMPILE_FLAGS})
