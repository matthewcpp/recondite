#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
# 
# This script based on the version from nvidia-texture-tools : https://code.google.com/p/nvidia-texture-tools

IF (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h 
		HINTS $ENV{GLEW_ROOT}/include
		DOC "The directory where GL/glew.h resides")
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES glew GLEW glew32 glew32s
		HINTS $ENV{GLEW_ROOT}/lib
		HINTS $ENV{GLEW_ROOT}/lib/Release/Win32
		DOC "The GLEW library")
ELSE ()
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		/usr/include
		/usr/local/include
		/opt/local/include
		DOC "The directory where GL/glew.h resides")
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES GLEW glew
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/opt/local/lib
		DOC "The GLEW library")
ENDIF ()

IF (GLEW_INCLUDE_PATH)
	SET( GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ELSE ()
	SET( GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ENDIF ()

MARK_AS_ADVANCED( GLEW_FOUND )