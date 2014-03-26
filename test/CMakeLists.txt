set(GTEST_MSVC_SEARCH "MT")
find_package(GTest REQUIRED)

file(GLOB file_list ${CMAKE_CURRENT_SOURCE_DIR}/math.cpp)

message("glob files: " ${file_list})

message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#link_directories (${HELLO_BINARY_DIR}/Hello) 
#add_executable(test_math file_list)