#pragma once

#ifdef RECONDITE_IMPORT_BUILD_SHARED
	#define RECONDITE_IMPORT_API __declspec(dllexport)
#else
	#define RECONDITE_IMPORT_API __declspec(dllimport)
#endif