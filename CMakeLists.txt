cmake_minimum_required(VERSION 2.8)

message("SDL_ROOT:" $ENV{SDL_ROOT})
message("GLEW_ROOT:" $ENV{GLEW_ROOT})
message("GTEST_ROOT:" $ENV{GTEST_ROOT})

project(recondite C CXX)

FIND_PACKAGE ( Threads REQUIRED )
find_package(OpenGL REQUIRED)

set(GLEW_INCLUDE_DIR ${GLEW_DIR}/include)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/platform)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${SDL_INCLUDE_DIR} )

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (recondite)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#build main recondite library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)




