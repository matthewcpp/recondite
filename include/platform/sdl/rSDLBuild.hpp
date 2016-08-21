#pragma once

#ifdef _MSC_VER
/*	disable DLL interface warning...templae classes will be private
class members which shoud prevent binary issues
*/
#pragma warning( disable : 4251)

#ifdef RECONDITE_SDL_BUILD_SHARED
#define RECONDITE_SDL_API __declspec(dllexport)
#else
#define RECONDITE_SDL_API __declspec(dllimport)
#endif

#else
#define RECONDITE_SDL_API

#endif