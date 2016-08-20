set (userinterface_files)
set (layout_files)

list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceApplication.cpp)

list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceController.hpp)
list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceController.cpp)

list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceModule.hpp)
list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceModule.cpp)

list(APPEND layout_files ${CMAKE_CURRENT_SOURCE_DIR}/userinterface/userinterface.xml)
list(APPEND layout_files ${CMAKE_CURRENT_SOURCE_DIR}/userinterface/userinterface.css)

source_group (source FILES ${userinterface_files})
source_group (layout FILES ${layout_files})

add_executable(userinterface WIN32 ${userinterface_files} ${layout_files})
set_target_properties(userinterface PROPERTIES FOLDER Samples)

#recondite
target_link_libraries(userinterface recondite rsdl rgl) 

#sdl
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(userinterface ${SDL2_LIBRARY})

#glew
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(userinterface ${GLEW_LIBRARY})