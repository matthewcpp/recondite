set(math_files)

add_rec_src(math_files "rMathUtil")
add_rec_src(math_files "rMatrix3")
add_rec_src(math_files "rMatrix4")
add_rec_src(math_files "rMatrixUtil")
add_rec_src(math_files "rQuaternion")
add_rec_src(math_files "rVector2")
add_rec_src(math_files "rVector3")
add_rec_src(math_files "rVector4")

set(recondite_files ${recondite_files} ${math_files} PARENT_SCOPE)
set(math_sources ${math_files} PARENT_SCOPE)