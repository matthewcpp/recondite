set(primitive_files)

add_rec_src(primitive_files "rPrimitive" "primitive")
add_rec_src(primitive_files "rPrimitiveBox" "primitive")
add_rec_src(primitive_files "rPrimitiveCone" "primitive")
add_rec_src(primitive_files "rPrimitiveCylinder" "primitive")
add_rec_src(primitive_files "rPrimitiveGrid" "primitive")
add_rec_src(primitive_files "rPrimitiveGeometry" "primitive")
add_rec_src(primitive_files "rPrimitiveSphere" "primitive")

list(APPEND primitive_files ${CMAKE_CURRENT_SOURCE_DIR}/../../include/primitive/rPrimitiveGeometryParams.hpp)


set(recondite_files ${recondite_files} ${primitive_files} PARENT_SCOPE)
set(primitive_sources ${primitive_files} PARENT_SCOPE)
