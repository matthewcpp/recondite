set(ui_files)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reApplication.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reApplication.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reMainFrame.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reMainFrame.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reOutliner.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reOutliner.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePalette.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePalette.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePaletteDropTarget.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePaletteDropTarget.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectExplorer.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reProjectExplorer.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyInspector.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyInspector.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyInterface.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/rePropertyInterface.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewport.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewport.cpp)

list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewportDisplay.hpp)
list(APPEND ui_files ${CMAKE_CURRENT_SOURCE_DIR}/reViewportDisplay.cpp)

set(ui_sources ${ui_files} PARENT_SCOPE)