#ifndef R_BUILD_HPP
#define R_BUILD_HPP

#ifdef _MSC_VER
	#ifdef RECONDITE_BUILD_SHARED
		#define RECONDITE_API __declspec(dllexport)
	#else
		#define RECONDITE_API __declspec(dllimport)
	#endif
#else
	#define RECONDITE_API
#endif

#endif