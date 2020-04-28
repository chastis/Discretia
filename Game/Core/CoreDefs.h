#pragma once

#if defined(M42_WINDOWS)
	#if defined(M42_CORE)
		#define CORE_DLL __declspec(dllexport)
		#define TEMPLATE_EXPORT_DLL
	#else 
		#define CORE_DLL __declspec(dllimport)
		#define TEMPLATE_EXPORT_DLL extern
	#endif

//Export some STL staff

#include <atomic>

TEMPLATE_EXPORT_DLL template struct CORE_DLL std::atomic<size_t>;

#else
	#define CORE_DLL
	#define TEMPLATE_EXPORT_DLL
#endif //M42_WINDOWS && M42_CORE