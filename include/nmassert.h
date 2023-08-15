#ifndef __NM_ASSERT_H__
#define __NM_ASSERT_H__
#include <cstdlib>
#include "stdio.h"

#define ASSERT_EXIT_CODE 3

#ifdef __NM__

#ifdef NDEBUG
#  define NMASSERT(condition) ((void)0)
#else
#  define NMASSERT(expr) if(!(expr)) { printf("Assertion \'%s\' failed:%s:%d\n", #expr, __FILE__, __LINE__); fflush(stdout); exit(ASSERT_EXIT_CODE); }
#endif

#ifdef NDEBUG
#   define NMASSERT_MSG(expr, ...) ((void)0)
#else
#   define NMASSERT_MSG(expr, ...) if(!(expr)) { printf("Assertion \'%s\' failed:%s:%d\t", #expr, __FILE__, __LINE__); \
                                    printf(__VA_ARGS__); \
                                    printf("\n"); \
                                    fflush(stdout);            \
                                    exit(ASSERT_EXIT_CODE); }
#endif

#endif //__NM__

#ifdef unix
#include "assert.h"
#  define NMASSERT(condition) assert(condition)
#endif

#ifdef _WIN32
#include <assert.h>
#  define NMASSERT(condition) assert(condition)
#endif

#endif //__NM_ASSERT_H__
