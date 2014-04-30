cmake_minimum_required(VERSION 2.8)

message("SDL Directory:" $ENV{SDLDIR})
message("GLEW_ROOT:" $ENV{GLEW_ROOT})
message("GTEST_ROOT:" $ENV{GTEST_ROOT})

project(recondite C CXX)

FIND_PACKAGE ( Threads REQUIRED )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (recondite)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/platform/rgl)
set(RGL_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/platform/rgl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)




