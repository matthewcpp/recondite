set (sdl_sources)

add_rec_platform_src(sdl_sources "rSDLApplication" "sdl")
add_rec_platform_src(sdl_sources "rSDLGraphicsDevice" "sdl")
add_rec_platform_src(sdl_sources "rSDLInputManager" "sdl")

list(APPEND sdl_sources ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/platform/sdl/rSDLBuild.hpp)
list(APPEND sdl_sources ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/platform/sdl/rSDLMain.hpp)

add_library( rsdl SHARED ${sdl_sources})
set_target_properties(rsdl PROPERTIES FOLDER Recondite)
add_definitions(-DRECONDITE_SDL_BUILD_SHARED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(rsdl recondite rgl) 
target_link_libraries(rsdl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

# In this case we are building a shared library and not want to link against sdl main
# Lets pull only the libsdl library out of the list and link that
set(sdl_lib)
list(GET SDL2_LIBRARY 1 sdl_lib)
target_link_libraries(rsdl ${sdl_lib})