set (private_files)

list(APPEND private_files ${CMAKE_CURRENT_LIST_DIR}/GameBase.Private.hpp)
list(APPEND private_files ${CMAKE_CURRENT_LIST_DIR}/GameBase.Private.cpp)
list(APPEND private_files ${CMAKE_CURRENT_LIST_DIR}/Application.Private.cpp)

source_group(Private FILES ${private_files})

target_sources(__GAME_NAME__ PRIVATE ${private_files})