#ifndef MODULE_H
#define MODULE_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <strstream>
#include <vector>

#include "NativeIncludes.h"

//==============================================================================
namespace squarepine
{
    #include "Maths.h"
    #include "Memory.h"

    #include "AffineTransform.h"
    #include "Point.h"
    #include "Line.h"
    #include "Range.h"
    #include "Rectangle.h"
    #include "RectangularBorder.h"

    #include "PixelFormats.h"
    #include "Colour.h"
    #include "Colours.h"

    #include "Threading/DynamicLibrary.h"

    #include "MissingOpenGLDefinitions.h"
    #include "OpenGLFunctions.h"
    #include "OpenGLHelpers.h"
    #include "OpenGLPixelFormat.h"
    #include "OpenGLContext.h"

    #include "Application.h"
    #include "Component.h"
    #include "Desktop.h"
    #include "Graphics.h"
    #include "Window.h"
}

#endif //MODULE_H