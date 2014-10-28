function(add_rec_src list_target name)
 	set (opt_params ${ARGN})
 	set (opt_params_length 0)
	list(LENGTH opt_params opt_params_length)
	
	set(temp)
	list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/${name}.cpp)

	if (${opt_params_length} GREATER 0)
		set(include_subdir)
		list(GET opt_params 0 include_subdir)
		list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${include_subdir}/${name}.hpp)
	else()
		list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${name}.hpp)
	endif()
	
	set(${list_target} ${${list_target}} ${temp} PARENT_SCOPE)
	
endfunction()

function(add_rec_platform_src list_target name include_subdir)

	set(temp)
	list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/${name}.cpp)
	list(APPEND temp ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/platform/${include_subdir}/${name}.hpp)
	
	set(${list_target} ${${list_target}} ${temp} PARENT_SCOPE)
	
endfunction()