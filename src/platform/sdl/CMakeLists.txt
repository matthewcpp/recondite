
set (sdl_files)

add_rec_platform_src(sdl_files "rSDLApplication" "sdl")
add_rec_platform_src(sdl_files "rSDLGraphicsDevice" "sdl")
add_rec_platform_src(sdl_files "rSDLInputManager" "sdl")

set(recondite_files ${recondite_files} ${sdl_files} PARENT_SCOPE)
set(sdl_sources ${sdl_files} PARENT_SCOPE)