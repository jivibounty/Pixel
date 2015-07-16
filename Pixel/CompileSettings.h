
#pragma once //CompileSettings.h

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#define PIXEL_WINAPI
#elif defined MACOSX
	#define PIXEL_MACOSX
#else
	#define PIXEL_LINUX
#endif

#if defined(_MSC_VER)
	#if defined(PIXEL_STATICLIB)
		#define PIXEL_API
	#else
		#if defined(PIXEL_SOURCE)
			// If we are building the DLL, export the symbols tagged like this
			#define PIXEL_API __declspec(dllexport)
		#else
			// If we are consuming the DLL, import the symbols tagged like this
			#define PIXEL_API __declspec(dllimport)
		#endif
	#endif
#elif defined(__GNUC__)
	#if defined(PIXEL_STATICLIB)
		#define PIXEL_API
	#else
		#if defined(PIXEL_SOURCE)
			#define PIXEL_API __attribute__ ((visibility ("default")))
		#else
			// If you use -fvisibility=hidden in GCC, exception handling and RTTI
			// would break if visibility wasn't set during export _and_ import
			// because GCC would immediately forget all type infos encountered.
			// See http://gcc.gnu.org/wiki/Visibility
			#define PIXEL_API __attribute__ ((visibility ("default")))
		#endif
	#endif
#else
	#ifdef PIXEL_WINAPI || __CYGWIN__
		#ifdef PIXEL_EXPORTS
			#define PIXEL_API __declspec(dllexport)
		#else
			#define PIXEL_API __declspec(dllimport)
		#endif
	#elif PIXEL_LINUX || PIXEL_MACOSX
		#define PIXEL_API
	#else
		#error Unknown compiler/platform, please implement shared library macros
	#endif
#endif

#if defined(_WIN32)
	#define PIXEL_CALLBACK __stdcall
#else
    #define PIXEL_CALLBACK
#endif

#if defined( _MSC_VER )

	#define PIXEL_BEGIN_ALIGNED( n, a )                            __declspec( align( a ) ) n
	#define PIXEL_END_ALIGNED( n, a )

#elif defined( __GNUC__ )

	#define PIXEL_BEGIN_ALIGNED( n, a )                            n
	#define PIXEL_END_ALIGNED( n, a )                              __attribute__( (aligned( a ) ) )

#else
		#error Unknown compiler/platform, please implement shared library macros
#endif

