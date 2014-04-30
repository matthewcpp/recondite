set(recondite_files)

set(asset_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/asset)
source_group (asset FILES ${asset_sources})

set(core_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
source_group (core FILES ${core_sources})

set(math_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
source_group (math FILES ${math_sources})

set(geometry_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geometry)
source_group (geometry FILES ${geometry_sources})

set(ui_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)
source_group (ui FILES ${ui_sources})

set(xml_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/xml)
source_group (xml FILES ${xml_sources})

set(log_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/log)
source_group (log FILES ${log_sources})

set(data_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/data)
source_group (data FILES ${data_sources})

set(input_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/input)
source_group (input FILES ${input_sources})

set(stream_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stream)
source_group (stream FILES ${stream_sources})

if (MSVC)
	set(win32_sources)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/platform/win32)
	source_group (win32 FILES ${win32_sources})
endif()

add_library( recondite SHARED ${recondite_files})

add_definitions(-DRECONDITE_BUILD_SHARED)