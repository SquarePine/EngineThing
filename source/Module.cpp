#include "Module.h"

#if SQUAREPINE_WINDOWS
    #include <windows.h>
#endif

namespace squarepine
{
    #include "AffineTransform.cpp"

    #include "Colour.cpp"
    #include "Colours.cpp"

    #include "OpenGLHelpers.cpp"
    #include "OpenGLPixelFormat.cpp"
    #include "OpenGLContext.cpp"

    #include "NativeWindows.cpp"
}
