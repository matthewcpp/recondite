set(importer_files)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/include/BuildImport.hpp)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/include/ImageImporter.hpp)
list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/src/ImageImporter.cpp)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/include/TextureAtlasImporter.hpp)
list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/src/TextureAtlasImporter.cpp)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/include/RectPacker.hpp)
list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/src/RectPacker.cpp)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/include/FontImporter.hpp)
list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/src/FontImporter.cpp)

list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/include/ModelImporter.hpp)
list(APPEND importer_files ${CMAKE_CURRENT_SOURCE_DIR}/src/ModelImporter.cpp)

add_library( rimport SHARED ${importer_files})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIR})

add_definitions(-DRECONDITE_IMPORT_BUILD_SHARED)

set_target_properties(rimport PROPERTIES FOLDER Tools)

target_link_libraries(rimport recondite ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARY})