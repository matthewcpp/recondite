set (geometry_test_files)

list(APPEND geometry_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rPlane_Test.cpp)

set(recondite_tests ${recondite_tests} ${geometry_test_files} PARENT_SCOPE)
set(geometry_tests ${geometry_test_files} PARENT_SCOPE)