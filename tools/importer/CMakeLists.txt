set(importer_files)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/Importer.hpp)
list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/Importer.cpp)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(rimporter ${importer_files})

set_target_properties(rimporter PROPERTIES FOLDER Tools)

target_link_libraries(rimporter recondite rimport)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../import/include)