#ifndef SQUAREPINE_OPENGL_HELPERS_H
#define SQUAREPINE_OPENGL_HELPERS_H

class OpenGLHelpers
{
public:
    /** Clears the GL error state. */
    static void resetErrorState();

    /** Clears the current context using the given colour. */
    static void clear (Colour colour);

    /** */
    static void enableScissorTest (Rectangle<int> clip);

    /** Checks whether the current context supports the specified extension. */
    static bool isExtensionSupported (const char* extensionName);

    /** Returns the address of a named GL extension function. */
    static void* getExtensionFunction (const char* functionName);
};

#endif //SQUAREPINE_OPENGL_HELPERS_H
