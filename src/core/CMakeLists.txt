set(core_files)

add_rec_src(core_files "rActor3")
add_rec_src(core_files "rContentManager")


set(recondite_files ${recondite_files} ${core_files} PARENT_SCOPE)
set(core_sources ${core_files} PARENT_SCOPE)

message("core files    " ${core_files})