set (selection_files)
set (layout_files)

list(APPEND selection_files ${CMAKE_CURRENT_SOURCE_DIR}/SelectionApplication.cpp)

list(APPEND selection_files ${CMAKE_CURRENT_SOURCE_DIR}/SelectionModule.hpp)
list(APPEND selection_files ${CMAKE_CURRENT_SOURCE_DIR}/SelectionModule.cpp)


list(APPEND layout_files ${CMAKE_CURRENT_SOURCE_DIR}/selection/selection.xml)
list(APPEND layout_files ${CMAKE_CURRENT_SOURCE_DIR}/selection/selection.css)

source_group (source FILES ${selection_files})
source_group (layout FILES ${layout_files})

add_executable(selection WIN32 ${selection_files} ${layout_files})
set_target_properties(selection PROPERTIES FOLDER Samples)

#recondite
target_link_libraries(selection recondite rsdl rgl) 

#sdl
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(selection ${SDL2_LIBRARY})

#glew
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(selection ${GLEW_LIBRARY})