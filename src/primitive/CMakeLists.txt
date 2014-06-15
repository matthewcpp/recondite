set(primitive_files)

add_rec_src(primitive_files "rPrimitiveBox" "primitive")

set(recondite_files ${recondite_files} ${primitive_files} PARENT_SCOPE)
set(primitive_sources ${primitive_files} PARENT_SCOPE)
