#ifndef R_BUILD_HPP
#define R_BUILD_HPP

#ifdef _MSC_VER
	/*	disable DLL interface warning...templae classes will be private
		class members which shoud prevent binary issues
	*/
	#pragma warning( disable : 4251)

	#ifdef RECONDITE_BUILD_SHARED
		#define RECONDITE_API __declspec(dllexport)
	#else
		#define RECONDITE_API __declspec(dllimport)
	#endif

	#ifdef RECONDITE_WX_BUILD_SHARED
		#define RECONDITE_RWX_CLASS __declspec(dllexport)
	#else
		#define RECONDITE_RWX_CLASS __declspec(dllimport)
	#endif
	
#else
	#define RECONDITE_API
	#define RECONDITE_RWX_CLASS
#endif

#endif