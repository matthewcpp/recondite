set(controller_files)

list(APPEND controller_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraController.hpp)

list(APPEND controller_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraUserController.hpp)
list(APPEND controller_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraUserController.cpp)

list(APPEND controller_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraOrientationController.hpp)
list(APPEND controller_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraOrientationController.cpp)


set(controller_sources ${controller_files} PARENT_SCOPE)