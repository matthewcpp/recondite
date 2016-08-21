
set (rgl_files)

add_rec_platform_src(rgl_files "rOpenGLContentManager" "rgl")
add_rec_platform_src(rgl_files "rOpenGLGraphicsDevice" "rgl")

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/platform/rgl/rglBuild.hpp)

set(rgl_shaders)

list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_drawing__.vert)
list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_drawing__.frag)

list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_primitive__.vert)
list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_primitive__.frag)

list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_sprite__.vert)
list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_sprite__.frag)

list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_text__.vert)
list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_text__.frag)

list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_model__.vert)
list(APPEND rgl_shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/__default_model__.frag)


set(recondite_files ${recondite_files} ${rgl_files} PARENT_SCOPE)

add_library( rgl SHARED ${rgl_files} ${rgl_shaders})

source_group (source FILES ${rgl_files})
source_group (shaders FILES ${rgl_shaders})

set_target_properties(rgl PROPERTIES FOLDER Recondite)
add_definitions(-DRECONDITE_GL_BUILD_SHARED)
target_link_libraries(rgl recondite) 
target_link_libraries(rgl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

#copy thr shaders to the default directory as a post build step
add_custom_command(TARGET rgl POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:rgl>/default)