set(dialog_files)

list(APPEND dialog_files ${CMAKE_CURRENT_SOURCE_DIR}/reNewProjectDialog.hpp)
list(APPEND dialog_files ${CMAKE_CURRENT_SOURCE_DIR}/reNewProjectDialog.cpp)

set(dialog_sources ${dialog_files} PARENT_SCOPE)