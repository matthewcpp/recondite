cmake_minimum_required(VERSION 2.8)

if (MSVC)
    message("SDL_ROOT:" $ENV{SDL_ROOT})
    message("GLEW_ROOT:" $ENV{GLEW_ROOT})
    message("GTEST_ROOT:" $ENV{GTEST_ROOT})
endif()

project(recondite C CXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)
find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/platform)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${SDL_INCLUDE_DIR} )

include (recondite)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET(GCC_COMPILE_FLAGS "-std=c++11")
	add_definitions(${GCC_COMPILE_FLAGS})
endif()

#build main recondite library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)




