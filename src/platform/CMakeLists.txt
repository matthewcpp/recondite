set(rgl_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rgl)

add_library( rgl SHARED ${rgl_sources})
set_target_properties(rgl PROPERTIES FOLDER Recondite)
add_definitions(-DRECONDITE_BUILD_SHARED)
target_link_libraries(rgl recondite) 
target_link_libraries(rgl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sdl)

