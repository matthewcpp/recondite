
set (rgl_files)

add_rec_platform_src(rgl_files "rOpenGLContentManager" "rgl")
add_rec_platform_src(rgl_files "rOpenGLGraphicsDevice" "rgl")

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/platform/rgl/rOpenGLDefaultShaders.inl)

set(recondite_files ${recondite_files} ${rgl_files} PARENT_SCOPE)
set(rgl_sources ${rgl_files} PARENT_SCOPE)