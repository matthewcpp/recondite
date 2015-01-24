set(editor_files)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reApplication.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reApplication.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reMainFrame.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reMainFrame.cpp)

set(editor_sources ${editor_files} PARENT_SCOPE)