#ifndef SQUAREPINE_OPENGL_FUNCTIONS_H
#define SQUAREPINE_OPENGL_FUNCTIONS_H

/** This class contains a generated list of OpenGL extension functions, which are either dynamically loaded
    for a specific GL context, or simply call-through to the appropriate OS function where available.
*/
struct OpenGLFunctions
{
    void initialise();
};

#endif //SQUAREPINE_OPENGL_FUNCTIONS_H
