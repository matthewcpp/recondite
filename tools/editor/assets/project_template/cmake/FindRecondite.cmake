#Finds Recondite Library
# This module defines
# RECONDITE_LIBRARIES, the names of the libraries to link against
# RECONDITE_FOUND, if false, do not try to link to recondite
# RECONDITE_INCLUDE_DIR, where to find recondite.hpp
include(FindPackageHandleStandardArgs) 

#get names of all required components for this build
SET(RECONDITE_SEARCH_LIBRARIES "recondite" "rgl" "rsdl")
#LIST(APPEND RECONDITE_SEARCH_LIBRARIES ${recondite_FIND_COMPONENTS})

SET(RECONDITE_LIBRARIES)

foreach(COMPONENT ${RECONDITE_SEARCH_LIBRARIES})
	FIND_LIBRARY(FOUND_COMPONENT${COMPONENT}
		NAMES ${COMPONENT}
		HINTS
		$ENV{RECONDITE_ROOT}
		PATH_SUFFIXES build/lib build/lib/Debug build/lib/Release
		PATHS ${RECONDITE_SEARCH_PATHS}
	)
	
	LIST(APPEND RECONDITE_LIBRARIES ${FOUND_COMPONENT${COMPONENT}})
endforeach()

SET(RECONDITE_SEARCH_PATHS
	~/recondite
)

FIND_PATH(RECONDITE_INCLUDE_DIR recondite.hpp
	HINTS
	$ENV{RECONDITE_ROOT}
	PATH_SUFFIXES include
	PATHS ${RECONDITE_SEARCH_PATHS}
)


FIND_PACKAGE_HANDLE_STANDARD_ARGS(RECONDITE REQUIRED_VARS RECONDITE_LIBRARIES RECONDITE_INCLUDE_DIR)