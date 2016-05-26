set (userinterface_files)

list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceApplication.cpp)

list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceController.hpp)
list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceController.cpp)

list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceModule.hpp)
list(APPEND userinterface_files ${CMAKE_CURRENT_SOURCE_DIR}/UserInterfaceModule.cpp)

add_executable(userinterface WIN32 ${userinterface_files})
set_target_properties(userinterface PROPERTIES FOLDER Samples)

#recondite
target_link_libraries(userinterface recondite rsdl rgl) 

#sdl
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(userinterface ${SDL2_LIBRARY})

#glew
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(userinterface ${GLEW_LIBRARY})