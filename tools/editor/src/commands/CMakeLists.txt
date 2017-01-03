set(command_files)

list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reActorCommands.hpp)
list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reActorCommands.cpp)

list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reSetPropertyCommand.hpp)
list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reSetPropertyCommand.cpp)

list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reTransformCommands.hpp)
list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reTransformCommands.cpp)

set(command_sources ${command_files} PARENT_SCOPE)