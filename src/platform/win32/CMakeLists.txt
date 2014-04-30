set(win32_files)

list(APPEND win32_files ${CMAKE_CURRENT_SOURCE_DIR}/rWin32ModuleLoader.cpp)

set(recondite_files ${recondite_files} ${win32_files} PARENT_SCOPE)
set(win32_sources ${win32_files} PARENT_SCOPE)