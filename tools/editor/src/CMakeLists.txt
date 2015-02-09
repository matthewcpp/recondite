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

set(property_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/properties)
source_group (PropertyConnectors FILES ${property_sources})
set(editor_files ${editor_files} ${property_sources})

#WIN32 specifies to use the "windows" subsystem, ie. win32 app.  wxWidgets GUI needs this project type
add_executable(editor WIN32 ${editor_files})
set_target_properties(editor PROPERTIES FOLDER Tools)

include(${wxWidgets_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../rwx)

target_link_libraries (editor recondite rgl rwx) 
target_link_libraries(editor ${wxWidgets_LIBRARIES})

add_definitions(-DWXUSINGDLL)