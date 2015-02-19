set(rwx_files)

list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxComponent.hpp)
list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxComponent.cpp)

list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxGLCanvas.hpp)
list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxGLCanvas.cpp)

list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxOpenGLGraphicsDevice.hpp)
list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxOpenGLGraphicsDevice.cpp)

list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxViewCameraInteraction.hpp)
list(APPEND rwx_files ${CMAKE_CURRENT_SOURCE_DIR}/rwxViewCameraInteraction.cpp)

add_library( rwx SHARED ${rwx_files})

add_definitions(-DWXUSINGDLL)
add_definitions(-DRECONDITE_WX_BUILD_SHARED)

set_target_properties(rwx PROPERTIES FOLDER Tools)

include(${wxWidgets_USE_FILE})

target_link_libraries(rwx recondite rgl)
target_link_libraries(rwx ${wxWidgets_LIBRARIES})