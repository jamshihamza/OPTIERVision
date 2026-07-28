#pragma once

#ifdef _WIN32

#ifdef OPTIER_COMMON_EXPORTS
#define OPTIER_COMMON_API __declspec(dllexport)
#else
#define OPTIER_COMMON_API __declspec(dllimport)
#endif

#else

#define OPTIER_COMMON_API

#endif