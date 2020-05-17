#pragma once

#if defined(M42_WINDOWS)
    #if defined(M42_CORE)
        #define CORE_API __declspec(dllexport)
        #define TEMPLATE_EXPORT_DLL
    #else 
        #define CORE_API __declspec(dllimport)
        #define TEMPLATE_EXPORT_DLL extern
    #endif

#pragma warning(disable:4251)

#else
    #define CORE_API
    #define TEMPLATE_EXPORT_DLL
#endif //M42_WINDOWS && M42_CORE