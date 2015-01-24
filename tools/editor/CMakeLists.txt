set (editor_sources)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

#WIN32 specifies to use the "windows" subsystem, ie. win32 app.  wxWidgets GUI needs this project type
add_executable(editor WIN32 ${editor_sources})

include(${wxWidgets_USE_FILE})

target_link_libraries (editor recondite rgl) 
target_link_libraries(editor ${wxWidgets_LIBRARIES})
add_definitions(-DWXUSINGDLL)