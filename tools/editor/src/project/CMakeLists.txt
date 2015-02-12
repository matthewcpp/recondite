set(project_files)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProject.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProject.cpp)

set(project_sources ${project_files} PARENT_SCOPE)