set(log_files)

add_rec_src(log_files "rLogFile" "log")
add_rec_src(log_files "rLogChain" "log")
add_rec_src(log_files "rLogStdOut" "log")

set(recondite_files ${recondite_files} ${log_files} PARENT_SCOPE)
set(log_sources ${log_files} PARENT_SCOPE)
