#pragma once
// windows x64 msvc
#ifdef KEXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#define K_API EXPORT