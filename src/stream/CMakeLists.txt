set(stream_files)

add_rec_src(stream_files "rIFileStream" "stream")
add_rec_src(stream_files "rOFileStream" "stream")
add_rec_src(stream_files "rIStream" "stream")
add_rec_src(stream_files "rOStream" "stream")

set(recondite_files ${recondite_files} ${stream_files} PARENT_SCOPE)
set(stream_sources ${stream_files} PARENT_SCOPE)
