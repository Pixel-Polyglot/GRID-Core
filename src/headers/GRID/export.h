#pragma once

#ifdef _WIN32
	#include <windows.h>
	#include <direct.h>
	#define getcwd _getcwd
	#define dlsym GetProcAddress
	#define PATH_MAX MAX_PATH
	#define HMODULE HMODULE
	#ifdef EXPORT_SHARED
		#define EXPORT __declspec(dllexport)
		#define EXPORT_FUNCTION extern "C" __declspec(dllexport)
	#else
		#define EXPORT __declspec(dllimport)
		#define EXPORT_FUNCTION extern "C" __declspec(dllimport)
	#endif
#else
	#include <unistd.h>
	#include <dlfcn.h>
	#define HMODULE void*
	#ifdef EXPORT_SHARED
		#define EXPORT __attribute__((visibility("default")))
		#define EXPORT_FUNCTION extern "C" __attribute__((visibility("default")))
	#else
		#define EXPORT
		#define EXPORT_FUNCTION
	#endif
#endif