#ifndef GO_ALGORITHMS_C_API_H_
#define GO_ALGORITHMS_C_API_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define ALGORITHMSCAPICALL __declspec(dllexport)
#else
#define ALGORITHMSCAPICALL
#endif

#ifdef __cplusplus
}
#endif

#endif