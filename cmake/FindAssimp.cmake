if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ASSIMP_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(ASSIMP_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)
	set(ASSIMP_ROOT_DIR CACHE PATH "ASSIMP root directory")

	# Find path of each library
	find_path(ASSIMP_INCLUDE_DIR
		NAMES
			assimp/anim.h
		HINTS
			${ASSIMP_ROOT_DIR}/include
	)

	if(MSVC12)
		set(ASSIMP_MSVC_VERSION "vc120")
	elseif(MSVC14)	
		set(ASSIMP_MSVC_VERSION "vc140")
	endif(MSVC12)
	
	if(MSVC12 OR MSVC14)
	
		find_path(ASSIMP_LIBRARY_DIR
			NAMES
				assimp-${ASSIMP_MSVC_VERSION}-mt.lib
			HINTS
				#binary distribution
				${ASSIMP_ROOT_DIR}/lib${ASSIMP_ARCHITECTURE}
				
				#in source build
				${ASSIMP_ROOT_DIR}/lib/Release 
				
				#out of source build
				${ASSIMP_ROOT_DIR}/build/code/Release
		)
		
		find_library(ASSIMP_LIBRARY				
			NAMES assimp-${ASSIMP_MSVC_VERSION}-mt.lib 			
			PATHS ${ASSIMP_LIBRARY_DIR}
		)
	
	endif()
	
else(WIN32)

	find_path(
	  ASSIMP_INCLUDE_DIR
	  NAMES 
		postprocess.h scene.h version.h config.h cimport.h
	  PATHS 
		/usr/include/assimp/
	)
	
	find_library(
	  ASSIMP_LIBRARY
	  NAMES assimp
	  PATHS /usr/local/lib/
	)
	
endif(WIN32)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Assimp REQUIRED_VARS ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY)


