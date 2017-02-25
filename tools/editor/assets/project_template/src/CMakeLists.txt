set (game_files)

#Public Section
list(APPEND game_files ${CMAKE_CURRENT_SOURCE_DIR}/Game.hpp)
list(APPEND game_files ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp)

add_executable(__GAME_NAME__ WIN32 ${game_files})

#recondite
include_directories(${RECONDITE_INCLUDE_DIR})
target_link_libraries(__GAME_NAME__ ${RECONDITE_LIBRARIES})

#sdl
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(__GAME_NAME__ ${SDL2_LIBRARY})

#glew
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(__GAME_NAME__ ${GLEW_LIBRARY})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(Private/CMakeLists.txt)
include(Behaviors/CMakeLists.txt)
include(Levels/CMakeLists.txt)