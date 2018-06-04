#if SQUAREPINE_WINDOWS

//==============================================================================
class OpenGLContext::Pimpl
{
public:
    Pimpl()
    {
    }

    ~Pimpl()
    {
    }

private:
};

OpenGLContext::OpenGLContext() :
    pimpl (new Pimpl())
{
}

OpenGLContext::~OpenGLContext()
{
    delete pimpl;
    pimpl = nullptr;
}

//==============================================================================
class Window::Pimpl
{
public:
    Pimpl (const OpenGLPixelFormat& pixelFormat)
    {
        PIXELFORMATDESCRIPTOR pfd;
        initialisePixelFormatDescriptor (pfd, pixelFormat);

        int pixFormat = ChoosePixelFormat (dc, &pfd);

        if (pixFormat != 0)
            SetPixelFormat (dc, pixFormat, &pfd);

        renderContext = wglCreateContext (dc);

        if (renderContext != nullptr)
        {
            makeActive();
            initialiseGLExtensions();

            auto wglFormat = wglChoosePixelFormatExtension (pixelFormat);
            deactivateCurrentContext();

            if (wglFormat != pixFormat && wglFormat != 0)
            {
                //Can't change the pixel format of a window, so need to delete the old one and create a new one.
                releaseDC();
                //nativeWindow = nullptr;
                //createNativeWindow (component);

                if (SetPixelFormat (dc, wglFormat, &pfd))
                {
                    deleteRenderContext();
                    renderContext = wglCreateContext (dc);
                }
            }

            //if (contextToShareWith != nullptr)
                //wglShareLists ((HGLRC) contextToShareWith, renderContext);
        }
    }

    ~Pimpl()
    {
        deleteRenderContext();
        releaseDC();
    }

private:
    HGLRC renderContext;
    HDC dc;

    void shutdownOnRenderThread()           { deactivateCurrentContext(); }

    static void deactivateCurrentContext()  { wglMakeCurrent (0, 0); }
    bool makeActive() const noexcept        { return isActive() || wglMakeCurrent (dc, renderContext) != FALSE; }
    bool isActive() const noexcept          { return wglGetCurrentContext() == renderContext; }
    void swapBuffers() const noexcept       { SwapBuffers (dc); }

    bool setSwapInterval (int numFramesPerSwap)
    {
        jassert (isActive()); // this can only be called when the context is active..
        return wglSwapIntervalEXT != nullptr && wglSwapIntervalEXT (numFramesPerSwap) != FALSE;
    }

    int getSwapInterval() const
    {
        jassert (isActive()); // this can only be called when the context is active..
        return wglGetSwapIntervalEXT != nullptr ? wglGetSwapIntervalEXT() : 0;
    }

    void updateWindowPosition (Rectangle<int> bounds)
    {
        /*if (nativeWindow != nullptr)
            SetWindowPos ((HWND) nativeWindow->getNativeHandle(), 0,
                          bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(),
                          SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOOWNERZORDER);*/
    }

    bool createdOk() const noexcept                 { return getRawContext() != nullptr; }
    void* getRawContext() const noexcept            { return renderContext; }
    unsigned int getFrameBufferID() const noexcept  { return 0; }

    void triggerRepaint()
    {
        //if (context != nullptr)
            //context->triggerRepaint();
    }

    #define SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION(name, returnType, params) \
        typedef returnType (__stdcall *type_ ## name) params; type_ ## name name;

    SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION (wglChoosePixelFormatARB,  BOOL, (HDC, const int*, const FLOAT*, UINT, int*, UINT*))
    SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION (wglSwapIntervalEXT,       BOOL, (int))
    SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION (wglGetSwapIntervalEXT,    int, ())
    #undef SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION

    void initialiseGLExtensions()
    {
        #define SQUAREPINE_INIT_WGL_FUNCTION(name)    name = (type_ ## name) OpenGLHelpers::getExtensionFunction (#name);
        SQUAREPINE_INIT_WGL_FUNCTION (wglChoosePixelFormatARB);
        SQUAREPINE_INIT_WGL_FUNCTION (wglSwapIntervalEXT);
        SQUAREPINE_INIT_WGL_FUNCTION (wglGetSwapIntervalEXT);
        #undef SQUAREPINE_INIT_WGL_FUNCTION
    }

    void createNativeWindow (Component&)
    {
        //dc = GetDC ((HWND) nativeWindow->getNativeHandle());
    }

    void deleteRenderContext()
    {
        if (renderContext != 0)
        {
            wglDeleteContext (renderContext);
            renderContext = 0;
        }
    }

    void releaseDC()
    {
        //ReleaseDC ((HWND) nativeWindow->getNativeHandle(), dc);
    }

    static void initialisePixelFormatDescriptor (PIXELFORMATDESCRIPTOR& pfd, const OpenGLPixelFormat& pixelFormat)
    {
        zerostruct (pfd);

        pfd.nSize           = sizeof (pfd);
        pfd.nVersion        = 1;
        pfd.dwFlags         = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        pfd.iPixelType      = PFD_TYPE_RGBA;
        pfd.iLayerType      = PFD_MAIN_PLANE;
        pfd.cColorBits      = (BYTE) (pixelFormat.redBits + pixelFormat.greenBits + pixelFormat.blueBits);
        pfd.cRedBits        = (BYTE) pixelFormat.redBits;
        pfd.cGreenBits      = (BYTE) pixelFormat.greenBits;
        pfd.cBlueBits       = (BYTE) pixelFormat.blueBits;
        pfd.cAlphaBits      = (BYTE) pixelFormat.alphaBits;
        pfd.cDepthBits      = (BYTE) pixelFormat.depthBufferBits;
        pfd.cStencilBits    = (BYTE) pixelFormat.stencilBufferBits;
        pfd.cAccumRedBits   = (BYTE) pixelFormat.accumulationBufferRedBits;
        pfd.cAccumGreenBits = (BYTE) pixelFormat.accumulationBufferGreenBits;
        pfd.cAccumBlueBits  = (BYTE) pixelFormat.accumulationBufferBlueBits;
        pfd.cAccumAlphaBits = (BYTE) pixelFormat.accumulationBufferAlphaBits;

        pfd.cAccumBits      = (BYTE) (pixelFormat.accumulationBufferRedBits
                                    + pixelFormat.accumulationBufferGreenBits
                                    + pixelFormat.accumulationBufferBlueBits
                                    + pixelFormat.accumulationBufferAlphaBits);
    }

    int wglChoosePixelFormatExtension (const OpenGLPixelFormat& pixelFormat) const
    {
        int format = 0;

        if (wglChoosePixelFormatARB != nullptr)
        {
            int atts[64] = { 0 };
            int n = 0;

            atts[n++] = WGL_DRAW_TO_WINDOW_ARB;  
            atts[n++] = GL_TRUE;
            atts[n++] = WGL_SUPPORT_OPENGL_ARB;  
            atts[n++] = GL_TRUE;
            atts[n++] = WGL_DOUBLE_BUFFER_ARB;   
            atts[n++] = GL_TRUE;
            atts[n++] = WGL_PIXEL_TYPE_ARB;      
            atts[n++] = WGL_TYPE_RGBA_ARB;
            atts[n++] = WGL_ACCELERATION_ARB;
            atts[n++] = WGL_FULL_ACCELERATION_ARB;

            atts[n++] = WGL_COLOR_BITS_ARB; 
            atts[n++] = pixelFormat.redBits + pixelFormat.greenBits + pixelFormat.blueBits;
            atts[n++] = WGL_RED_BITS_ARB;   
            atts[n++] = pixelFormat.redBits;
            atts[n++] = WGL_GREEN_BITS_ARB; 
            atts[n++] = pixelFormat.greenBits;
            atts[n++] = WGL_BLUE_BITS_ARB;  
            atts[n++] = pixelFormat.blueBits;
            atts[n++] = WGL_ALPHA_BITS_ARB; 
            atts[n++] = pixelFormat.alphaBits;
            atts[n++] = WGL_DEPTH_BITS_ARB; 
            atts[n++] = pixelFormat.depthBufferBits;

            atts[n++] = WGL_STENCIL_BITS_ARB;      
            atts[n++] = pixelFormat.stencilBufferBits;
            atts[n++] = WGL_ACCUM_RED_BITS_ARB;    
            atts[n++] = pixelFormat.accumulationBufferRedBits;
            atts[n++] = WGL_ACCUM_GREEN_BITS_ARB;  
            atts[n++] = pixelFormat.accumulationBufferGreenBits;
            atts[n++] = WGL_ACCUM_BLUE_BITS_ARB;   
            atts[n++] = pixelFormat.accumulationBufferBlueBits;
            atts[n++] = WGL_ACCUM_ALPHA_BITS_ARB;  
            atts[n++] = pixelFormat.accumulationBufferAlphaBits;

            if (pixelFormat.multisamplingLevel > 0
                && OpenGLHelpers::isExtensionSupported ("GL_ARB_multisample"))
            {
                atts[n++] = WGL_SAMPLE_BUFFERS_ARB;
                atts[n++] = 1;
                atts[n++] = WGL_SAMPLES_ARB;
                atts[n++] = pixelFormat.multisamplingLevel;
            }

            atts[n++] = 0;
            jassert (n <= numElementsInArray (atts));

            UINT formatsCount = 0;
            wglChoosePixelFormatARB (dc, atts, nullptr, 1, &format, &formatsCount);
        }

        return format;
    }
};

//==============================================================================
static OpenGLPixelFormat pixelFormat;

Window::Window() :
    pimpl (new Pimpl (pixelFormat))
{
}

Window::~Window()
{
    delete pimpl;
    pimpl = nullptr;
}

#endif //SQUAREPINE_WINDOWS
