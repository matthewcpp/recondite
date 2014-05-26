set (basicscene_files)

list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicScenePlugin.hpp)
list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicScenePlugin.cpp)

list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicSceneModule.hpp)
list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicSceneModule.cpp)

add_library(basicscene SHARED ${basicscene_files})
set_target_properties(basicscene PROPERTIES IMPORT_PREFIX "")
set_target_properties(basicscene PROPERTIES SUFFIX ".rec")

include_directories(${SDL_INCLUDE_DIR})
target_link_libraries (basicscene recondite) 