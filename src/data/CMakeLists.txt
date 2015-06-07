set(data_files)

add_rec_src(data_files "rImmediateBuffer" "data")
add_rec_src(data_files "rSkeletonData" "data")

set(recondite_files ${recondite_files} ${data_files} PARENT_SCOPE)
set(data_sources ${data_files} PARENT_SCOPE)
