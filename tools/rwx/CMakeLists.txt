set(rwx_files)

list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxGLCanvas.hpp)
list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxGLCanvas.cpp)

add_library( rwx SHARED ${rwx_files})

add_definitions(-DWXUSINGDLL)
add_definitions(-DRECONDITE_BUILD_SHARED)

set_target_properties(rwx PROPERTIES FOLDER Tools)

include(${wxWidgets_USE_FILE})

target_link_libraries(rwx recondite rgl)
target_link_libraries(rwx ${wxWidgets_LIBRARIES})