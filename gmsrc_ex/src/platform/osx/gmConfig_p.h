/*
_____               __  ___          __            ____        _      __
/ ___/__ ___ _  ___ /  |/  /__  ___  / /_____ __ __/ __/_______(_)__  / /_
/ (_ / _ `/  ' \/ -_) /|_/ / _ \/ _ \/  '_/ -_) // /\ \/ __/ __/ / _ \/ __/
\___/\_,_/_/_/_/\__/_/  /_/\___/_//_/_/\_\\__/\_, /___/\__/_/ /_/ .__/\__/
/___/             /_/


See Copyright Notice in gmMachine.h


*/

#ifndef _GMCONFIG_P_H_
#define _GMCONFIG_P_H_

//#include <malloc.h>  // alloca
#include <new>
#include <cassert>

//#define _DEBUG // Manually enable for debug build if compiler doesn't

// pragmas


// system defines

#define GM_LITTLE_ENDIAN      1
#define GM_COMPILER_GCC
#define GM_X86

#if defined(__LP64__) // 64bit target
	#define GM_DEFAULT_ALLOC_ALIGNMENT 16
	#define GM_PTR_SIZE_64 // Ptr size is 64bit
#else // 32bit target
	#define GM_DEFAULT_ALLOC_ALIGNMENT 4
	#define GM_PTR_SIZE_32 // Ptr size is 32bit
#endif

#define GM_CDECL
#ifdef _DEBUG
#define GM_ASSERT(A)        assert(A)
#else //_DEBUG
#define GM_ASSERT(A)
#endif //_DEBUG
#define GM_NL                 "\r\n" // "\n"
#define GM_FORCEINLINE        inline  // inline
#define GM_INLINE             inline
#define _gmstricmp            strcasecmp
#define _gmsnprintf           snprintf // snprintf
#define _gmvsnprintf          vsnprintf // vsnprintf
#ifdef _DEBUG
#define GM_DEBUG_BUILD
#endif // _DEBUG
#define GM_PRINTF             printf

#define GM_NEW( alloc_params ) new alloc_params
#define GM_PLACEMENT_NEW( alloc_params, address ) new(address) alloc_params

#define GM_MAKE_ID32( a, b, c, d )  ( ((d)<<24) | ((c)<<16) | ((b)<<8) | (a))

#define GM_MIN_FLOAT32        -3.402823466e38f
#define GM_MAX_FLOAT32        3.402823466e38f

#define GM_MIN_FLOAT64        -1.7976931348623158e308
#define GM_MAX_FLOAT64        1.7976931348623158e308

#define GM_SMALLEST_FLOAT32   1.175494351e-38f
#define GM_SMALLEST_FLOAT64   2.2250738585072014e-308

#define GM_MIN_UINT8          0
#define GM_MAX_UINT8          255

#define GM_MIN_INT8           -128
#define GM_MAX_INT8           127

#define GM_MIN_UINT16         0
#define GM_MAX_UINT16         65535
#define GM_MIN_INT16          -32768
#define GM_MAX_INT16          32767

#define GM_MIN_UINT32         0
#define GM_MAX_UINT32         4294967295
#define GM_MIN_INT32          -2147483648
#define GM_MAX_INT32          2147483647

#define GM_MAX_INT            2147483647
#define GM_MAX_SHORT          32767

#define GM_MAX_CHAR_STRING    256
#define GM_MAX_PATH           256

// basic types
typedef const char * LPCTSTR;
typedef int32_t gmint;
typedef uint32_t gmuint;
typedef float gmfloat;
typedef char gmint8;
typedef uint8_t gmuint8;
typedef int16_t gmint16;
typedef uint16_t gmuint16;
typedef int32_t gmint32;
typedef uint32_t gmuint32;

// typedef intptr_t gmptr; // machine pointer size as int
// typedef uintptr_t gmuptr; // machine pointer size as int

typedef int64_t gmint64;
typedef uint64_t gmuint64;

// machine pointer size as int
#if defined(__LP64__)
typedef int64_t gmptr;
typedef uint64_t gmuptr;
#else
typedef int32_t gmptr;
typedef uint32_t gmuptr;
#endif

#undef GM_CRT_DEBUG

#endif // _GMCONFIG_P_H_
