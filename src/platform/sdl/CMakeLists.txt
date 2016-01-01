set (sdl_sources)

add_rec_platform_src(sdl_sources "rSDLApplication" "sdl")
add_rec_platform_src(sdl_sources "rSDLGraphicsDevice" "sdl")
add_rec_platform_src(sdl_sources "rSDLInputManager" "sdl")

add_library( rsdl SHARED ${sdl_sources})
set_target_properties(rsdl PROPERTIES FOLDER Recondite)
add_definitions(-DRECONDITE_BUILD_SHARED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(rsdl recondite rgl) 
target_link_libraries(rsdl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
target_link_libraries(rsdl ${SDL2_LIBRARY})