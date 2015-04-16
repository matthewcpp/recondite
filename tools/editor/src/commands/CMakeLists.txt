set(command_files)

list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reDeleteActorCommand.hpp)
list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reDeleteActorCommand.cpp)

list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reInsertActorCommand.hpp)
list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reInsertActorCommand.cpp)

list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reTranslateCommand.hpp)
list(APPEND command_files ${CMAKE_CURRENT_SOURCE_DIR}/reTranslateCommand.cpp)

set(command_sources ${command_files} PARENT_SCOPE)