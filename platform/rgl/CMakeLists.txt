find_package(OpenGL REQUIRED)

set (rgl_files)

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLContentManager.hpp)
list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLContentManager.cpp)

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLGraphicsDevice.hpp)
list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLGraphicsDevice.cpp)

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLDefaultShaders.inl)

add_library( rgl_static STATIC ${rgl_files})
include_directories( ${OPENGL_INCLUDE_DIRS} )
target_link_libraries(rgl_static ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )