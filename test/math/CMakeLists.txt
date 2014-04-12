set (math_test_files)

list(APPEND math_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rMath_Test.cpp)
list(APPEND math_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rVector3_Test.cpp)
list(APPEND math_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rQuaternion_Test.cpp)

set(recondite_tests ${recondite_tests} ${math_test_files} PARENT_SCOPE)
set(math_tests ${math_test_files} PARENT_SCOPE)