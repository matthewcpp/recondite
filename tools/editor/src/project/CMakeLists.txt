set(project_files)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProject.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProject.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectBuilder.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectBuilder.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectResourceManager.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectResourceManager.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectAssets.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectAssets.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectCode.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectCode.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectLevels.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectLevels.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reComponent.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reComponent.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reSelectionManager.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reSelectionManager.cpp)

list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reUtils.hpp)
list(APPEND project_files ${CMAKE_CURRENT_SOURCE_DIR}/reUtils.cpp)

set(project_sources ${project_files} PARENT_SCOPE)