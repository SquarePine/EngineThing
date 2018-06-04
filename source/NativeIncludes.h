#ifndef NATIVE_INCLUDES_H
#define NATIVE_INCLUDES_H

#if _DEBUG || ! defined (NDEBUG)
    #define SQUAREPINE_DEBUG 1
#endif

//==============================================================================
#if _WINDOWS && (_WIN32 || _WIN64)

#define SQUAREPINE_MSVC 1
#define SQUAREPINE_WINDOWS 1

#undef NOMINMAX
#define NOMINMAX 1

#undef _ALLOW_KEYWORD_MACROS
#define _ALLOW_KEYWORD_MACROS 1

#if __cplusplus_winrt
#else
    #include <tchar.h>
    #include <windowsx.h>

    #ifndef APIENTRY
        #define APIENTRY __stdcall
        #define CLEAR_TEMP_APIENTRY 1
    #endif

    #ifndef WINGDIAPI
        #define WINGDIAPI __declspec (dllimport)
        #define CLEAR_TEMP_WINGDIAPI 1
    #endif

    #if SQUAREPINE_MINGW
        #include <GL/gl.h>
    #else
        #include <gl/GL.h>
    #endif

    #ifdef CLEAR_TEMP_WINGDIAPI
        #undef WINGDIAPI
        #undef CLEAR_TEMP_WINGDIAPI
    #endif

    #ifdef CLEAR_TEMP_APIENTRY
        #undef APIENTRY
        #undef CLEAR_TEMP_APIENTRY
    #endif

    #pragma comment (lib, "OpenGL32.Lib")
#endif //__cplusplus_winrt
#endif //_WINDOWS

//==============================================================================
#undef Rectangle
#undef Point

#undef min
#undef _min
#undef MIN
#undef _MIN
#undef max
#undef _max
#undef MAX
#undef _MAX

//==============================================================================
#if SQUAREPINE_GCC || SQUAREPINE_CLANG
    #define SQUAREPINE_PACKED __attribute__((packed))
#else
    /** */
    #define SQUAREPINE_PACKED
#endif

//==============================================================================
#if SQUAREPINE_DEBUG || DOXYGEN
    /** A platform-independent way of forcing an inline function.

        Use the syntax:
        @code
            forcedinline void myFunction() {}
        @endcode
    */
    #define forcedinline  inline
#else
   #if SQUAREPINE_MSVC
    #define forcedinline __forceinline
   #else
    #define forcedinline inline __attribute__ (always_inline)
   #endif
#endif

/** This macro defines the C calling convention used as the standard for JUCE calls. */
#if SQUAREPINE_MSVC
    #define SQUAREPINE_CALLTYPE __stdcall
    #define SQUAREPINE_CDECL    __cdecl
#else
    #define SQUAREPINE_CALLTYPE
    #define SQUAREPINE_CDECL
#endif

//==============================================================================
#undef jassert
#define jassert(x) assert(x)

#if defined (_MSC_VER) && _MSC_VER < 1900
    #undef noexcept
    #define noexcept throw()
#endif

#if defined (_MSC_VER) && _MSC_VER < 1700
    #undef override
    #define override

    #undef final
    #define final
#endif

#endif //NATIVE_INCLUDES_H
