set(recondite_files)

set(math_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
source_group (math FILES ${math_sources})

set(core_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
source_group (core FILES ${core_sources})

add_library( recondite_static STATIC ${recondite_files})