set(recondite_tests)

set(math_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
source_group (math FILES ${math_tests})

set(core_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
source_group (core FILES ${core_tests})

set(geometry_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geometry)
source_group (geometry FILES ${geometry_tests})

set(ui_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)
source_group (ui FILES ${ui_tests})

set(stream_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stream)
source_group (stream FILES ${stream_tests})

set (common_files)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/testcommon)
source_group (common FILES ${common_files})

add_executable(recondite_test ${recondite_tests})
set_target_properties(recondite_test PROPERTIES FOLDER Recondite)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/testcommon)

target_link_libraries (recondite_test recondite ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) 

if (MSVC)
	add_definitions(-D_VARIADIC_MAX=10)
endif()
