#ifndef SQUAREPINE_OPENGL_CONTEXT_H
#define SQUAREPINE_OPENGL_CONTEXT_H

/** Creates an OpenGL context.
*/
class OpenGLContext final
{
public:
    /** Constructor. */
    OpenGLContext();

    /** Destructor. */
    ~OpenGLContext();

    void update() {}
    void draw() {}

    class Pimpl;
    Pimpl* pimpl;

private:
};

#endif //SQUAREPINE_OPENGL_CONTEXT_H
