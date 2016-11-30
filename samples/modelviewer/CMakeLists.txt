set (modelviewer_files)
set (layout_files)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerApplication.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerController.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerController.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerModule.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerModule.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerSettings.hpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerCamera.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerCamera.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/SkeletonGeometry.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/SkeletonGeometry.cpp)

list(APPEND layout_files ${CMAKE_CURRENT_SOURCE_DIR}/modelviewer/modelviewer.xml)
list(APPEND layout_files ${CMAKE_CURRENT_SOURCE_DIR}/modelviewer/modelviewer.css)

source_group (source FILES ${modelviewer_files})
source_group (layout FILES ${layout_files})

add_executable(modelviewer WIN32 ${modelviewer_files} ${layout_files})
set_target_properties(modelviewer PROPERTIES FOLDER Samples)

#recondite
target_link_libraries(modelviewer recondite rsdl rgl) 

#sdl
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(modelviewer ${SDL2_LIBRARY})

#glew
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(modelviewer ${GLEW_LIBRARY})