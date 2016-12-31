set(tool_files)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolManager.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolManager.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reTools.hpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolBase.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolBase.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reSelectionTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reSelectionTool.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reTranslateTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reTranslateTool.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reGizmo.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reGizmo.cpp)

set(tool_sources ${tool_files} PARENT_SCOPE)