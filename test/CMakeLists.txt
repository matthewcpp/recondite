set(GTEST_MSVC_SEARCH "MT")
find_package(GTest REQUIRED)

set(recondite_tests)

set(math_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
source_group (math FILES ${math_tests})

set(core_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
source_group (core FILES ${core_tests})

add_executable(recondite_test ${recondite_tests})

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries (recondite_test recondite_static ${GTEST_BOTH_LIBRARIES}) 

if (MSVC)
	add_definitions(-D_VARIADIC_MAX=10)
endif()