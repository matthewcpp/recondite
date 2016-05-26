cmake_minimum_required(VERSION 2.8)

project(recondite C CXX)

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
    message("GTEST_ROOT:" $ENV{GTEST_ROOT})
	message("WX_ROOT:" $ENV{WX_ROOT})
	message("FREETYPE_ROOT:" $ENV{FREETYPE_ROOT})
	message("ASSIMP_ROOT:" $ENV{ASSIMP_ROOT})
	
	set(ASSIMP_ROOT_DIR $ENV{ASSIMP_ROOT})
	set(ENV{FREETYPE_DIR} $ENV{FREETYPE_ROOT})
	set(ENV{SDL2DIR} $ENV{SDL2_ROOT})
	
	#configure wxmsw build variables
	set(wxWidgets_ROOT_DIR $ENV{WX_ROOT})
	set(wxWidgets_LIB_DIR ${wxWidgets_ROOT_DIR}/lib/vc_dll)
	set(wxWidgets_CONFIGURATION "mswud")
	
endif()

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GTest REQUIRED)
find_package(Freetype REQUIRED)
find_package(SDL2 REQUIRED)
find_package(wxWidgets COMPONENTS gl aui adv core base propgrid xml REQUIRED)
find_package(Assimp REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/platform)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

include (recondite)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/platform)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools)




