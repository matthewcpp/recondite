set (stream_test_files)

list(APPEND stream_test_files ${CMAKE_CURRENT_SOURCE_DIR}/rArchiveEntryStream_Test.cpp)

set(recondite_tests ${recondite_tests} ${stream_test_files} PARENT_SCOPE)
set(stream_tests ${stream_test_files} PARENT_SCOPE)