set (ui_test_files)

list(APPEND ui_test_files ${CMAKE_CURRENT_SOURCE_DIR}/ruiButton_Test.cpp)
list(APPEND ui_test_files ${CMAKE_CURRENT_SOURCE_DIR}/ruiCheckbox_Test.cpp)


set(recondite_tests ${recondite_tests} ${ui_test_files} PARENT_SCOPE)
set(ui_tests ${ui_test_files} PARENT_SCOPE)