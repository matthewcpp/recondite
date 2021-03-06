set(editor_files)

set(project_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/project)
source_group (Project FILES ${project_sources})
set(editor_files ${editor_files} ${project_sources})

set(ui_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)
source_group (UI FILES ${ui_sources})
set(editor_files ${editor_files} ${ui_sources})

set(tool_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools)
source_group (Tools FILES ${tool_sources})
set(editor_files ${editor_files} ${tool_sources})

set(command_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/commands)
source_group (Commands FILES ${command_sources})
set(editor_files ${editor_files} ${command_sources})

set(dialog_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dialogs)
source_group (Dialogs FILES ${dialog_sources})
set(editor_files ${editor_files} ${dialog_sources})

set(controller_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/controllers)
source_group (Controllers FILES ${controller_sources})
set(editor_files ${editor_files} ${controller_sources})

#WIN32 specifies to use the "windows" subsystem, ie. win32 app.  wxWidgets GUI needs this project type
add_executable(editor WIN32 ${editor_files})
set_target_properties(editor PROPERTIES FOLDER Tools)

include(${wxWidgets_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../rwx)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../import/include)

target_link_libraries (editor recondite rgl rwx rimport) 
target_link_libraries(editor ${wxWidgets_LIBRARIES})

add_definitions(-DWXUSINGDLL)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()