set(property_files)

list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyConnector.hpp)
list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyConnectors.hpp)

list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/reActorPropertyConnector.hpp)
list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/reActorPropertyConnector.cpp)

list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraPropertyConnector.hpp)
list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/reCameraPropertyConnector.cpp)

list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitivePropertyConnector.hpp)
list(APPEND property_files ${CMAKE_CURRENT_SOURCE_DIR}/rePrimitivePropertyConnector.cpp)

set(property_sources ${property_files} PARENT_SCOPE)