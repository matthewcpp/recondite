set (core_test_files)

list(APPEND core_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rAnimation_Test.cpp)
list(APPEND core_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rAnimationCurve_Test.cpp)
list(APPEND core_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rAnimationPlayer_Test.cpp)
list(APPEND core_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rArrayString_Test.cpp)

set(recondite_tests ${recondite_tests} ${core_test_files} PARENT_SCOPE)
set(core_tests ${core_test_files} PARENT_SCOPE)