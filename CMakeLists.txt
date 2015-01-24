cmake_minimum_required(VERSION 2.8)

project(recondite C CXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#compiler specific configuration settings

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	SET(GCC_COMPILE_FLAGS "-std=c++11")
	add_definitions(${GCC_COMPILE_FLAGS})
elseif (MSVC)
    message("SDL_ROOT:" $ENV{SDL_ROOT})
    message("GLEW_ROOT:" $ENV{GLEW_ROOT})
    message("GTEST_ROOT:" $ENV{GTEST_ROOT})
	message("WX_ROOT:" $ENV{WX_ROOT})
	
	#configure wxmsw build variables
	set(wxWidgets_ROOT_DIR $ENV{WX_ROOT})
	set(wxWidgets_LIB_DIR ${wxWidgets_ROOT_DIR}/lib/vc_lib)
	set(wxWidgets_CONFIGURATION "mswud")
	
endif()

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)
find_package(GTest REQUIRED)
find_package(wxWidgets COMPONENTS gl adv core base REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/platform)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${SDL_INCLUDE_DIR} )

include (recondite)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/platform)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools/editor)




