set(editor_files)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reApplication.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reApplication.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reMainFrame.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reMainFrame.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reOutliner.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reOutliner.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectExplorer.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectExplorer.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyInspector.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyInspector.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewport.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewport.cpp)

list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewportDisplay.hpp)
list(APPEND editor_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewportDisplay.cpp)

set(editor_sources ${editor_files} PARENT_SCOPE)