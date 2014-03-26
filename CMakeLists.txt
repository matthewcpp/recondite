cmake_minimum_required(VERSION 2.8)

message("SDL Directory:" $ENV{SDL_DIR})
message("GLEW Directory:" $ENV{GLEW_DIR})
message("gtest Directory:" $ENV{GTEST_ROOT})

project(recondite)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (recondite)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/platform/rgl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)




