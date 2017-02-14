cmake_minimum_required(VERSION 3.1)

project(__GAME_NAME__ C CXX)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#compiler specific configuration settings

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	SET(GCC_COMPILE_FLAGS "-std=c++11")
	add_definitions(${GCC_COMPILE_FLAGS})
elseif (MSVC)
    message("SDL2_ROOT:" $ENV{SDL2_ROOT})
    message("GLEW_ROOT:" $ENV{GLEW_ROOT})
	message("RECONDITE_ROOT:" $ENV{RECONDITE_ROOT})
	
	set(ENV{SDL2DIR} $ENV{SDL2_ROOT})
endif()

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(recondite REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

