OpenGLPixelFormat::OpenGLPixelFormat (const int bitsPerRGBComponent,
                                      const int alphaBits_,
                                      const int depthBufferBits_,
                                      const int stencilBufferBits_) noexcept :
    redBits (bitsPerRGBComponent),
    greenBits (bitsPerRGBComponent),
    blueBits (bitsPerRGBComponent),
    alphaBits (alphaBits_),
    depthBufferBits (depthBufferBits_),
    stencilBufferBits (stencilBufferBits_),
    accumulationBufferRedBits (0),
    accumulationBufferGreenBits (0),
    accumulationBufferBlueBits (0),
    accumulationBufferAlphaBits (0),
    multisamplingLevel (0)
{
}

bool OpenGLPixelFormat::operator== (const OpenGLPixelFormat& other) const noexcept
{
    return redBits == other.redBits
        && greenBits == other.greenBits
        && blueBits  == other.blueBits
        && alphaBits == other.alphaBits
        && depthBufferBits == other.depthBufferBits
        && stencilBufferBits == other.stencilBufferBits
        && accumulationBufferRedBits   == other.accumulationBufferRedBits
        && accumulationBufferGreenBits == other.accumulationBufferGreenBits
        && accumulationBufferBlueBits  == other.accumulationBufferBlueBits
        && accumulationBufferAlphaBits == other.accumulationBufferAlphaBits
        && multisamplingLevel == other.multisamplingLevel;
}

bool OpenGLPixelFormat::operator!= (const OpenGLPixelFormat& other) const noexcept
{
    return ! operator== (other);
}
