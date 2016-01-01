set(converter_files)

list(APPEND converter_files ${CMAKE_CURRENT_SOURCE_DIR}/Converter.hpp)
list(APPEND converter_files ${CMAKE_CURRENT_SOURCE_DIR}/Converter.cpp)

list(APPEND converter_files ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(rconverter ${converter_files})

set_target_properties(rconverter PROPERTIES FOLDER Tools)

target_link_libraries(rconverter recondite rimport)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../import/include)