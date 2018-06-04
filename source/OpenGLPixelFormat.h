#ifndef SQUAREPINE_OPENGL_PIXEL_FORMAT_H
#define SQUAREPINE_OPENGL_PIXEL_FORMAT_H

/** Represents the various properties of an OpenGL pixel format.

    @see OpenGLContext::setPixelFormat
*/
class OpenGLPixelFormat
{
public:
    /** Creates an OpenGLPixelFormat.
        The default constructor just initialises the object as a simple 8-bit
        RGBA format.
    */
    OpenGLPixelFormat (int bitsPerRGBComponent = 8,
                       int alphaBits = 8,
                       int depthBufferBits = 16,
                       int stencilBufferBits = 0) noexcept;

    bool operator== (const OpenGLPixelFormat&) const noexcept;
    bool operator!= (const OpenGLPixelFormat&) const noexcept;

    //==============================================================================
    int redBits;                        /**< The number of bits per pixel to use for the red channel. */
    int greenBits;                      /**< The number of bits per pixel to use for the green channel. */
    int blueBits;                       /**< The number of bits per pixel to use for the blue channel. */
    int alphaBits;                      /**< The number of bits per pixel to use for the alpha channel. */

    int depthBufferBits;                /**< The number of bits per pixel to use for a depth buffer. */
    int stencilBufferBits;              /**< The number of bits per pixel to use for a stencil buffer. */

    int accumulationBufferRedBits;      /**< The number of bits per pixel to use for an accumulation buffer's red channel. */
    int accumulationBufferGreenBits;    /**< The number of bits per pixel to use for an accumulation buffer's green channel. */
    int accumulationBufferBlueBits;     /**< The number of bits per pixel to use for an accumulation buffer's blue channel. */
    int accumulationBufferAlphaBits;    /**< The number of bits per pixel to use for an accumulation buffer's alpha channel. */

    unsigned char multisamplingLevel;   /**< The number of samples to use for full-scene multisampled anti-aliasing (if available). */
};

#endif //SQUAREPINE_OPENGL_PIXEL_FORMAT_H
