set(stream_files)

list(APPEND stream_files ${CMAKE_CURRENT_SOURCE_DIR}/../../include/stream/rIStream.hpp)
list(APPEND stream_files ${CMAKE_CURRENT_SOURCE_DIR}/../../include/stream/rOStream.hpp)

add_rec_src(stream_files "rIFileStream" "stream")
add_rec_src(stream_files "rIStringStream" "stream")
add_rec_src(stream_files "rOFileStream" "stream")
add_rec_src(stream_files "rOStringStream" "stream")

set(recondite_files ${recondite_files} ${stream_files} PARENT_SCOPE)
set(stream_sources ${stream_files} PARENT_SCOPE)
