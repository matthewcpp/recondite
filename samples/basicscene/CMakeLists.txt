set (basicscene_files)

list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicSceneApplication.cpp)

list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicSceneModule.hpp)
list(APPEND basicscene_files ${CMAKE_CURRENT_SOURCE_DIR}/BasicSceneModule.cpp)

add_executable(basicscene ${basicscene_files})
set_target_properties(basicscene PROPERTIES FOLDER Samples)

include_directories(${SDL_INCLUDE_DIR})

target_link_libraries(basicscene recondite rsdl rgl) 

