find_package(SDL REQUIRED)

set (rec_files)

list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLApplication.hpp)
list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLApplication.cpp)

list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLGraphicsDevice.hpp)
list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLGraphicsDevice.cpp)

list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLInputManager.hpp)
list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLInputManager.cpp)

list(APPEND rec_files ${CMAKE_CURRENT_SOURCE_DIR}/rSDLMain.cpp)

add_executable( rec ${rec_files})

include_directories( ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${RGL_INCLUDE_DIRECTORY})
target_link_libraries(rec rgl recondite ${SDL_LIBRARY} ${SDLMAIN_LIBRARY})