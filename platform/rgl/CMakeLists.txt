find_package(OpenGL REQUIRED)

set(GLEW_INCLUDE_DIR ${GLEW_DIR}/include)

find_package(GLEW REQUIRED)

set (rgl_files)

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLContentManager.hpp)
list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLContentManager.cpp)

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLGraphicsDevice.hpp)
list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLGraphicsDevice.cpp)

list(APPEND rgl_files ${CMAKE_CURRENT_SOURCE_DIR}/rOpenGLDefaultShaders.inl)

add_library( rgl SHARED ${rgl_files})

add_definitions(-DRECONDITE_BUILD_SHARED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH})
target_link_libraries(rgl recondite ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})