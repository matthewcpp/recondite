set(geometry_files)

add_rec_src(geometry_files "rAlignedBox3")
add_rec_src(geometry_files "rGeometryUtil")
add_rec_src(geometry_files "rLine3")
add_rec_src(geometry_files "rCircle2")

set(recondite_files ${recondite_files} ${geometry_files} PARENT_SCOPE)
set(geometry_sources ${geometry_files} PARENT_SCOPE)
