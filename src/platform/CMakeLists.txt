set(rgl_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rgl)

add_library( rgl SHARED ${rgl_sources})
set_target_properties(rgl PROPERTIES FOLDER Recondite)
add_definitions(-DRECONDITE_BUILD_SHARED)
target_link_libraries(rgl recondite) 
target_link_libraries(rgl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

set(sdl_sources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sdl)

add_library( rsdl SHARED ${sdl_sources})
set_target_properties(rsdl PROPERTIES FOLDER Recondite)
add_definitions(-DRECONDITE_BUILD_SHARED)
target_link_libraries(rsdl recondite rgl) 
target_link_libraries(rsdl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
target_link_libraries(rsdl ${SDL_LIBRARY} ${SDLMAIN_LIBRARY})