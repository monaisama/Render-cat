#pragma once
// windows x64 msvc
#if true
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#endif

#ifdef KEXPORT
    #define K_API EXPORT
#else
    #define K_API IMPORT
#endif