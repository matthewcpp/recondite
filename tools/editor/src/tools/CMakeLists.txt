set(tool_files)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolManager.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolManager.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reTools.hpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolBase.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reToolBase.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitiveBoxTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitiveBoxTool.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitiveGridTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitiveGridTool.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitiveConeTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitiveConeTool.cpp)

list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reSelectionTool.hpp)
list(APPEND tool_files ${CMAKE_CURRENT_SOURCE_DIR}/reSelectionTool.cpp)

set(tool_sources ${tool_files} PARENT_SCOPE)