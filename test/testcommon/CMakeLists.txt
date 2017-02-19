set (common_test_files)

list(APPEND common_test_files ${CMAKE_CURRENT_SOURCE_DIR}/TestFilesystem.hpp)
list(APPEND common_test_files ${CMAKE_CURRENT_SOURCE_DIR}/TestFilesystem.cpp)

set(recondite_tests ${recondite_tests} ${common_test_files} PARENT_SCOPE)
set(common_files ${common_test_files} PARENT_SCOPE)