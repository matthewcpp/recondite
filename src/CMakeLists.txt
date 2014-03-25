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

add_library( recondite_static STATIC ${recondite_files})