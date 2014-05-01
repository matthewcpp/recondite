set (modelviewer_files)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/rDemoCamera.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/rDemoCamera.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/rDemoModule.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/rDemoModule.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/rDemoPawn.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/rDemoPawn.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ruiDemoController.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ruiDemoController.cpp)

list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerPlugin.hpp)
list(APPEND modelviewer_files ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewerPlugin.cpp)

add_library(modelviewer SHARED ${modelviewer_files})
set_target_properties(modelviewer PROPERTIES IMPORT_PREFIX "")
set_target_properties(modelviewer PROPERTIES SUFFIX ".rec")

include_directories(${SDL_INCLUDE_DIR})
target_link_libraries (modelviewer recondite) 