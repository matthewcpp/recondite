function(add_rec_src list_target name)
	set(temp)
	list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/${name}.cpp)
	list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${name}.hpp)
	
	set(${list_target} ${${list_target}} ${temp} PARENT_SCOPE)
	
endfunction()