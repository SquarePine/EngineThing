#if SQUAREPINE_WINDOWS

typedef void (*SettingChangeCallbackFunc) (void);
extern SettingChangeCallbackFunc settingChangeCallback;

static void forceDisplayUpdate()
{
    //const_cast<Desktop::Displays&> (Desktop::getInstance().getDisplays()).refresh();

    //ModifierKeys::updateCurrentModifiers();
    //component.parentSizeChanged();
    //handleMovedOrResized();
}

static bool isStandaloneApp()
{
    return true;
}

//==============================================================================
//Process class shit:

static void* currentModuleHandle = nullptr;

static void* SQUAREPINE_CALLTYPE getCurrentModuleInstanceHandle() noexcept
{
    if (currentModuleHandle == nullptr)
    {
        BOOL status = GetModuleHandleExA (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                          (LPCSTR) &currentModuleHandle, (HMODULE*) &currentModuleHandle);

        if (status == FALSE || currentModuleHandle == nullptr)
            currentModuleHandle = GetModuleHandleA (nullptr);
    }

    return currentModuleHandle;
}

void* getUser32Function (const char* functionName)
{
    HMODULE module = GetModuleHandleA ("user32.dll");
    jassert (module != nullptr);
    return (void*) GetProcAddress (module, functionName);
}


//==============================================================================
#ifndef WM_TOUCH
 enum
 {
     WM_TOUCH         = 0x0240,
     TOUCHEVENTF_MOVE = 0x0001,
     TOUCHEVENTF_DOWN = 0x0002,
     TOUCHEVENTF_UP   = 0x0004
 };

 typedef HANDLE HTOUCHINPUT;
 typedef HANDLE HGESTUREINFO;

 struct TOUCHINPUT
 {
     LONG         x;
     LONG         y;
     HANDLE       hSource;
     DWORD        dwID;
     DWORD        dwFlags;
     DWORD        dwMask;
     DWORD        dwTime;
     ULONG_PTR    dwExtraInfo;
     DWORD        cxContact;
     DWORD        cyContact;
 };

 struct GESTUREINFO
 {
     UINT         cbSize;
     DWORD        dwFlags;
     DWORD        dwID;
     HWND         hwndTarget;
     POINTS       ptsLocation;
     DWORD        dwInstanceID;
     DWORD        dwSequenceID;
     ULONGLONG    ullArguments;
     UINT         cbExtraArgs;
 };
#endif

#ifndef WM_NCPOINTERUPDATE
    enum
    {
        WM_NCPOINTERUPDATE       = 0x241,
        WM_NCPOINTERDOWN         = 0x242,
        WM_NCPOINTERUP           = 0x243,
        WM_POINTERUPDATE         = 0x245,
        WM_POINTERDOWN           = 0x246,
        WM_POINTERUP             = 0x247,
        WM_POINTERENTER          = 0x249,
        WM_POINTERLEAVE          = 0x24A,
        WM_POINTERACTIVATE       = 0x24B,
        WM_POINTERCAPTURECHANGED = 0x24C,
        WM_TOUCHHITTESTING       = 0x24D,
        WM_POINTERWHEEL          = 0x24E,
        WM_POINTERHWHEEL         = 0x24F,
        WM_POINTERHITTEST        = 0x250
    };

    enum
    {
        PT_TOUCH = 0x00000002,
        PT_PEN   = 0x00000003
    };

    enum POINTER_BUTTON_CHANGE_TYPE
    {
        POINTER_CHANGE_NONE,
        POINTER_CHANGE_FIRSTBUTTON_DOWN,
        POINTER_CHANGE_FIRSTBUTTON_UP,
        POINTER_CHANGE_SECONDBUTTON_DOWN,
        POINTER_CHANGE_SECONDBUTTON_UP,
        POINTER_CHANGE_THIRDBUTTON_DOWN,
        POINTER_CHANGE_THIRDBUTTON_UP,
        POINTER_CHANGE_FOURTHBUTTON_DOWN,
        POINTER_CHANGE_FOURTHBUTTON_UP,
        POINTER_CHANGE_FIFTHBUTTON_DOWN,
        POINTER_CHANGE_FIFTHBUTTON_UP
    };

    enum
    {
        PEN_MASK_NONE      = 0x00000000,
        PEN_MASK_PRESSURE  = 0x00000001,
        PEN_MASK_ROTATION  = 0x00000002,
        PEN_MASK_TILT_X    = 0x00000004,
        PEN_MASK_TILT_Y    = 0x00000008
    };

    enum
    {
        TOUCH_MASK_NONE        = 0x00000000,
        TOUCH_MASK_CONTACTAREA = 0x00000001,
        TOUCH_MASK_ORIENTATION = 0x00000002,
        TOUCH_MASK_PRESSURE    = 0x00000004
    };

    enum
    {
        POINTER_FLAG_NONE           = 0x00000000,
        POINTER_FLAG_NEW            = 0x00000001,
        POINTER_FLAG_INRANGE        = 0x00000002,
        POINTER_FLAG_INCONTACT      = 0x00000004,
        POINTER_FLAG_FIRSTBUTTON    = 0x00000010,
        POINTER_FLAG_SECONDBUTTON   = 0x00000020,
        POINTER_FLAG_THIRDBUTTON    = 0x00000040,
        POINTER_FLAG_FOURTHBUTTON   = 0x00000080,
        POINTER_FLAG_FIFTHBUTTON    = 0x00000100,
        POINTER_FLAG_PRIMARY        = 0x00002000,
        POINTER_FLAG_CONFIDENCE     = 0x00004000,
        POINTER_FLAG_CANCELED       = 0x00008000,
        POINTER_FLAG_DOWN           = 0x00010000,
        POINTER_FLAG_UPDATE         = 0x00020000,
        POINTER_FLAG_UP             = 0x00040000,
        POINTER_FLAG_WHEEL          = 0x00080000,
        POINTER_FLAG_HWHEEL         = 0x00100000,
        POINTER_FLAG_CAPTURECHANGED = 0x00200000,
        POINTER_FLAG_HASTRANSFORM   = 0x00400000
    };

    typedef DWORD  POINTER_INPUT_TYPE;
    typedef UINT32 POINTER_FLAGS;
    typedef UINT32 PEN_FLAGS;
    typedef UINT32 PEN_MASK;
    typedef UINT32 TOUCH_FLAGS;
    typedef UINT32 TOUCH_MASK;

    struct POINTER_INFO
    {
        POINTER_INPUT_TYPE    pointerType;
        UINT32          pointerId;
        UINT32          frameId;
        POINTER_FLAGS   pointerFlags;
        HANDLE          sourceDevice;
        HWND            hwndTarget;
        POINT           ptPixelLocation;
        POINT           ptHimetricLocation;
        POINT           ptPixelLocationRaw;
        POINT           ptHimetricLocationRaw;
        DWORD           dwTime;
        UINT32          historyCount;
        INT32           InputData;
        DWORD           dwKeyStates;
        UINT64          PerformanceCount;
        POINTER_BUTTON_CHANGE_TYPE ButtonChangeType;
    };

    struct POINTER_TOUCH_INFO
    {
        POINTER_INFO    pointerInfo;
        TOUCH_FLAGS     touchFlags;
        TOUCH_MASK      touchMask;
        RECT            rcContact;
        RECT            rcContactRaw;
        UINT32          orientation;
        UINT32          pressure;
    };

    struct POINTER_PEN_INFO
    {
        POINTER_INFO    pointerInfo;
        PEN_FLAGS       penFlags;
        PEN_MASK        penMask;
        UINT32          pressure;
        UINT32          rotation;
        INT32           tiltX;
        INT32           tiltY;
    };

    #define GET_POINTERID_WPARAM(wParam)    (LOWORD(wParam))
#endif

#ifndef MONITOR_DPI_TYPE
    enum Monitor_DPI_Type
    {
        MDT_Effective_DPI  = 0,
        MDT_Angular_DPI    = 1,
        MDT_Raw_DPI        = 2,
        MDT_Default        = MDT_Effective_DPI
    };

    enum Process_DPI_Awareness
    {
        Process_DPI_Unaware            = 0,
        Process_System_DPI_Aware       = 1,
        Process_Per_Monitor_DPI_Aware  = 2
    };
#endif

typedef BOOL (WINAPI* RegisterTouchWindowFunc) (HWND, ULONG);
typedef BOOL (WINAPI* GetTouchInputInfoFunc) (HTOUCHINPUT, UINT, TOUCHINPUT*, int);
typedef BOOL (WINAPI* CloseTouchInputHandleFunc) (HTOUCHINPUT);
typedef BOOL (WINAPI* GetGestureInfoFunc) (HGESTUREINFO, GESTUREINFO*);
typedef BOOL (WINAPI* SetProcessDPIAwareFunc)();
typedef BOOL (WINAPI* SetProcessDPIAwarenessFunc) (Process_DPI_Awareness);
typedef HRESULT (WINAPI* GetDPIForMonitorFunc) (HMONITOR, Monitor_DPI_Type, UINT*, UINT*);

static RegisterTouchWindowFunc registerTouchWindow = nullptr;
static GetTouchInputInfoFunc getTouchInputInfo = nullptr;
static CloseTouchInputHandleFunc closeTouchInputHandle = nullptr;
static GetGestureInfoFunc getGestureInfo = nullptr;
static SetProcessDPIAwareFunc setProcessDPIAware = nullptr;
static SetProcessDPIAwarenessFunc setProcessDPIAwareness = nullptr;
static GetDPIForMonitorFunc getDPIForMonitor = nullptr;

static bool hasCheckedForMultiTouch = false;

static bool canUseMultiTouch()
{
    if (registerTouchWindow == nullptr && ! hasCheckedForMultiTouch)
    {
        hasCheckedForMultiTouch = true;

        registerTouchWindow   = (RegisterTouchWindowFunc)   getUser32Function ("RegisterTouchWindow");
        getTouchInputInfo     = (GetTouchInputInfoFunc)     getUser32Function ("GetTouchInputInfo");
        closeTouchInputHandle = (CloseTouchInputHandleFunc) getUser32Function ("CloseTouchInputHandle");
        getGestureInfo        = (GetGestureInfoFunc)        getUser32Function ("GetGestureInfo");
    }

    return registerTouchWindow != nullptr;
}

static void setMessageFilter (HWND windowHandle)
{
    typedef BOOL (WINAPI* ChangeWindowMessageFilterExFunc) (HWND, UINT, DWORD, PVOID);

    if (ChangeWindowMessageFilterExFunc changeMessageFilter = (ChangeWindowMessageFilterExFunc) getUser32Function ("ChangeWindowMessageFilterEx"))
    {
        changeMessageFilter (windowHandle, WM_DROPFILES, 1 /*MSGFLT_ALLOW*/, nullptr);
        changeMessageFilter (windowHandle, WM_COPYDATA, 1 /*MSGFLT_ALLOW*/, nullptr);
        changeMessageFilter (windowHandle, 0x49, 1 /*MSGFLT_ALLOW*/, nullptr);
    }
}

//==============================================================================
typedef BOOL (WINAPI* GetPointerTypeFunc) (UINT32, POINTER_INPUT_TYPE*);
typedef BOOL (WINAPI* GetPointerTouchInfoFunc) (UINT32, POINTER_TOUCH_INFO*);
typedef BOOL (WINAPI* GetPointerPenInfoFunc) (UINT32, POINTER_PEN_INFO*);

static GetPointerTypeFunc      getPointerTypeFunction = nullptr;
static GetPointerTouchInfoFunc getPointerTouchInfo = nullptr;
static GetPointerPenInfoFunc   getPointerPenInfo = nullptr;

static bool canUsePointerAPI = false;

static void checkForPointerAPI()
{
    getPointerTypeFunction = (GetPointerTypeFunc) getUser32Function ("GetPointerType");
    getPointerTouchInfo    = (GetPointerTouchInfoFunc) getUser32Function ("GetPointerTouchInfo");
    getPointerPenInfo      = (GetPointerPenInfoFunc) getUser32Function ("GetPointerPenInfo");

    canUsePointerAPI = getPointerTypeFunction != nullptr
                       && getPointerTouchInfo != nullptr
                       && getPointerPenInfo != nullptr;
}

//==============================================================================
static void setDPIAwareness()
{
   #if ! JUCE_DISABLE_WIN32_DPI_AWARENESS
    if (isStandaloneApp())
    {
        if (setProcessDPIAwareness == nullptr)
        {
            HMODULE shcoreModule = GetModuleHandleA ("SHCore.dll");

            if (shcoreModule != nullptr)
            {
                setProcessDPIAwareness = (SetProcessDPIAwarenessFunc) GetProcAddress (shcoreModule, "SetProcessDpiAwareness");
                getDPIForMonitor = (GetDPIForMonitorFunc) GetProcAddress (shcoreModule, "GetDpiForMonitor");

                if (setProcessDPIAwareness != nullptr && getDPIForMonitor != nullptr
//                     && SUCCEEDED (setProcessDPIAwareness (Process_Per_Monitor_DPI_Aware)))
                     && SUCCEEDED (setProcessDPIAwareness (Process_System_DPI_Aware))) // (keep using this mode temporarily..)
                    return;
            }

            if (setProcessDPIAware == nullptr)
            {
                setProcessDPIAware = (SetProcessDPIAwareFunc) getUser32Function ("SetProcessDPIAware");

                if (setProcessDPIAware != nullptr)
                    setProcessDPIAware();
            }
        }
    }
   #endif
}

static double getGlobalDPI()
{
    setDPIAwareness();

    HDC dc = GetDC (nullptr);
    const double dpi = (double) (GetDeviceCaps (dc, LOGPIXELSX) + GetDeviceCaps (dc, LOGPIXELSY)) / 2.0;
    ReleaseDC (nullptr, dc);
    return dpi;
}

//==============================================================================
/** Returns the number of currently-active peers.
    @see getPeer
*/
static int getNumPeers() noexcept
{
    return 1;
}

/** Returns one of the currently-active peers.
    @see getNumPeers
*/
static WindowPeer* getPeer (int index) noexcept
{
    return nullptr;
}

/** Checks if this peer object is valid.
    @see getNumPeers
*/
static bool isValidPeer (const WindowPeer* peer) noexcept
{
    return peer != nullptr;
}

//==============================================================================
static DynamicLibrary opengl32dll;

static void* getOpenGLFunction (const std::string& name)
{
    void* p = (void*) wglGetProcAddress (name.c_str());
    if (p == nullptr
        || p == (void*) 0x1
        || p == (void*) 0x2
        || p == (void*) 0x3
        || p == (void*) -1)
    {
        if (opengl32dll.getNativeHandle() == nullptr)
        {
            opengl32dll.open ("opengl32.dll");
        }

        if (opengl32dll.getNativeHandle() != nullptr)
        {
            return opengl32dll.getFunction (name);
        }
    }

    return nullptr;
}

#define SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION(name, returnType, params) \
    typedef returnType (__stdcall *type_ ## name) params; type_ ## name name;

SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION (wglChoosePixelFormatARB,  BOOL, (HDC, const int*, const FLOAT*, UINT, int*, UINT*))
SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION (wglSwapIntervalEXT,       BOOL, (int))
SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION (wglGetSwapIntervalEXT,    int, ())
#undef SQUAREPINE_DECLARE_WGL_EXTENSION_FUNCTION

void initialiseGLExtensions()
{
    #define SQUAREPINE_INIT_WGL_FUNCTION(name) \
        name = (type_ ## name) getOpenGLFunction (#name);

    SQUAREPINE_INIT_WGL_FUNCTION (wglChoosePixelFormatARB);
    SQUAREPINE_INIT_WGL_FUNCTION (wglSwapIntervalEXT);
    SQUAREPINE_INIT_WGL_FUNCTION (wglGetSwapIntervalEXT);
    #undef JUCE_INIT_WGL_FUNCTION
}

//==============================================================================
class OpenGLContext::Pimpl
{
public:
    Pimpl() :
        renderContext (nullptr)
    {
    }

    ~Pimpl()
    {
    }

    HGLRC renderContext;
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
class WindowPeer
{
public:
    WindowPeer() :
        shouldDraw (true)
    {
    }

    ~WindowPeer()
    {
    }

    bool shouldDraw;

    //==============================================================================
    LRESULT CALLBACK updateWindowProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_CREATE:
                if (GetDC (hWnd) == nullptr)
                    return -1;
            break;

		    case WM_CLOSE:
			    DestroyWindow (hWnd);
                return 0;

            case WM_ACTIVATE:
            {
                // The message WM_ACTIVE is sent whenever the application has focus.
                // For example if the application is minimised then it is not in focus.
                // As the application is not in focus it is pointless wasting clock
                // cycles and graphics hardware to render to what cannot be seen.
                shouldDraw = static_cast<BOOL> (wParam) != FALSE;
                return 0;
            }

            case WM_PAINT:
            {
                static TCHAR greeting[] = _T ("Hello, World!");

                PAINTSTRUCT ps = { 0 };
                HDC hdc = BeginPaint (hWnd, &ps);
                TextOut (hdc, 5, 5, greeting, _tcslen (greeting));
                EndPaint (hWnd, &ps);
                return 0;
            }

            case WM_DESTROY:
            {
                PostQuitMessage (0);
                return 0;
            }

            default:
            break;
        }

        return DefWindowProc (hWnd, message, wParam, lParam);
    }

private:
};

//==============================================================================
namespace SquarePineWindowIdentifier
{
    LONG_PTR getImprobableWindowNumber() noexcept
    {
        static LONG_PTR number = (LONG_PTR) rand(); //@todo Should be a huge fucking number range... not a measly rand() shit thing.
        return number;
    }

    bool isSquarePineWindow (HWND windowHandle) noexcept
    {
        return windowHandle != nullptr && GetWindowLongPtr (windowHandle, GWLP_USERDATA) == getImprobableWindowNumber();
    }

    void setAsSquarePineWindow (HWND windowHandle, bool isSquarePineWindow) noexcept
    {
        SetWindowLongPtr (windowHandle, GWLP_USERDATA, isSquarePineWindow ? getImprobableWindowNumber() : 0);
    }

    WindowPeer* getOwnerOfWindow (HWND windowHandle) noexcept
    {
        if (isSquarePineWindow (windowHandle))
            return (WindowPeer*) GetWindowLongPtr (windowHandle, 8);

        return nullptr;
    }

    LRESULT CALLBACK updateWindowProcedure (HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (WindowPeer* peer = getOwnerOfWindow (windowHandle))
        {
            jassert (isValidPeer (peer));
            return peer->updateWindowProcedure (windowHandle, message, wParam, lParam);
        }

        return DefWindowProcW (windowHandle, message, wParam, lParam);
    }
}

//==============================================================================
class WindowClassHolder
{
public:
    WindowClassHolder() :
        atom (0)
    {
        //This name has to be different for each app/dll instance because otherwise poor old Windows can
        //get a bit confused (even despite it not being a process-global window class).
        static std::wstring windowClassName;

        {
            std::wstringstream ss;
            ss << L"SquarePine_";

            for (int i = std::max (3, std::abs (rand())); --i >= 0;)
                ss << rand();

            windowClassName = ss.str();
        }

        WNDCLASSEX info     = { 0 };
        info.cbSize         = sizeof (info);
        info.style          = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        info.lpfnWndProc    = (WNDPROC) SquarePineWindowIdentifier::updateWindowProcedure;
        info.hInstance      = (HINSTANCE) getCurrentModuleInstanceHandle();
        info.lpszClassName  = windowClassName.c_str();
        info.cbWndExtra     = 32;
        info.hIcon          = LoadIcon (info.hInstance, MAKEINTRESOURCE (IDI_APPLICATION));
        info.hIconSm        = LoadIcon (info.hInstance, MAKEINTRESOURCE (IDI_APPLICATION));

        atom = RegisterClassEx (&info);
        jassert (atom != 0);
    }

    ~WindowClassHolder() 
    {
        if (getNumPeers() == 0)
            UnregisterClass (getWindowClassName(), (HINSTANCE) getCurrentModuleInstanceHandle());

        //clearSingletonInstance();
    }

    LPCTSTR getWindowClassName() const noexcept { return (LPCTSTR) (pointer_sized_uint) atom; }

private:
    ATOM atom;
};

static WindowClassHolder* windowClassHolder; //@todo Should be a controlled singleton!

//==============================================================================
class Window::Pimpl
{
public:
    Pimpl (const std::string& title, const OpenGLPixelFormat& pf) :
        parentWindowToAddTo (nullptr),
        styleFlags (windowHasTitleBar | windowIsResizable),
        windowHandle (nullptr),
        dc (nullptr),
        pixelFormat (pf)
    {
    }

    bool hasStyle (int value) const noexcept { return (styleFlags & value) != 0; }
    bool hasTitleBar() const noexcept { return hasStyle (windowHasTitleBar); }

    void createWindow()
    {
        DWORD type = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

        if (hasTitleBar())
        {
            type |= WS_OVERLAPPED;

            if (hasStyle (windowHasCloseButton))
            {
                type |= WS_SYSMENU;
            }
            else
            {
                //Annoyingly, Windows won't let you have a min/max button without a close button
                jassert (hasStyle (windowHasMinimiseButton | windowHasMaximiseButton));
            }

            if (hasStyle (windowIsResizable))
                type |= WS_THICKFRAME;
        }
        else if (parentWindowToAddTo != nullptr)
        {
            type |= WS_CHILD;
        }
        else
        {
            type |= WS_POPUP | WS_SYSMENU;
        }

        DWORD extendedStyle = 0;
        if (hasStyle (windowAppearsOnTaskbar))
            extendedStyle |= WS_EX_TOOLWINDOW;
        else
            extendedStyle |= WS_EX_APPWINDOW;

        if (hasStyle (windowHasMinimiseButton))     type |= WS_MINIMIZEBOX;
        if (hasStyle (windowHasMaximiseButton))     type |= WS_MAXIMIZEBOX;
        if (hasStyle (windowIgnoresMouseClicks))    extendedStyle |= WS_EX_TRANSPARENT;
        if (hasStyle (windowIsSemiTransparent))     extendedStyle |= WS_EX_LAYERED;

       #if 0
        windowHandle = CreateWindow (windowClassName, windowsTitle,
                                     WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                     800, 600, nullptr, nullptr, hInstance, nullptr);
       #else
        windowHandle = CreateWindowEx (extendedStyle, windowClassHolder->getWindowClassName(),
                                       L"", type, 0, 0, 0, 0, parentWindowToAddTo, 0,
                                       (HINSTANCE) getCurrentModuleInstanceHandle(), 0);
       #endif

        if (windowHandle == nullptr)
        {
            jassert (true); //Got fucking rekt here, buddy
            exit (EXIT_FAILURE);
        }

        SetWindowLongPtr (windowHandle, 0, 0);
        SetWindowLongPtr (windowHandle, 8, (LONG_PTR) this);
        SquarePineWindowIdentifier::setAsSquarePineWindow (windowHandle, true);

#if 0
        if (dropTarget == nullptr)
        {
            WindowPeer* peer = nullptr;

            if (dontRepaint)
                peer = getOwnerOfWindow (parentToAddTo);

            if (peer == nullptr)
                peer = this;

            dropTarget = new FileDropTarget (*peer);
        }

        RegisterDragDrop (hwnd, dropTarget);
#endif

        if (canUseMultiTouch())
            registerTouchWindow (windowHandle, 0);

        setDPIAwareness();
        setMessageFilter (windowHandle);
        updateBorderSize();
        checkForPointerAPI();

        // This is needed so that our plugin window gets notified of WM_SETTINGCHANGE messages
        // and can respond to display scale changes
        if (! isStandaloneApp())
            settingChangeCallback = forceDisplayUpdate; //This should recursively update all windows the app has on the desktop, hidden and shown

        // Calling this function here is (for some reason) necessary to make Windows
        // correctly enable the menu items that we specify in the wm_initmenu message.
        GetSystemMenu (windowHandle, false);

        PIXELFORMATDESCRIPTOR pfd = { 0 };
        initialisePixelFormatDescriptor (pfd, pixelFormat);

        const int pixFormat = ChoosePixelFormat (dc, &pfd);

        if (pixFormat != 0)
            SetPixelFormat (dc, pixFormat, &pfd);

        renderContext = wglCreateContext (dc);

        if (renderContext != nullptr)
        {
            makeActive();
            initialiseGLExtensions();

            const int wglFormat = wglChoosePixelFormatExtension (pixelFormat);
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

    static void* createWindowCallback (void* userData)
    {
        static_cast<Pimpl*> (userData)->createWindow();
        return nullptr;
    }

    ~Pimpl()
    {
        deleteRenderContext();
        releaseDC();
    }

    void setTitle (const std::string& title)
    {
        SetWindowTextA (windowHandle, title.c_str());
    }

    void update()
    {
    }

    void draw()
    {
    }

    void* getNativeHandle() const
    {
        return windowHandle;
    }

private:
    HWND parentWindowToAddTo;
    int styleFlags;
    HWND windowHandle;
    HDC dc;
    RectangularBorder<int> windowBorder;
    OpenGLPixelFormat pixelFormat;

    void updateBorderSize()
    {
        WINDOWINFO info = { 0 };
        info.cbSize = sizeof (info);

        if (GetWindowInfo (windowHandle, &info) != FALSE)
            windowBorder = RectangularBorder<int> (info.rcClient.top - info.rcWindow.top,
                                                   info.rcClient.left - info.rcWindow.left,
                                                   info.rcWindow.bottom - info.rcClient.bottom,
                                                   info.rcWindow.right - info.rcClient.right);
    }

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

    void createNativeWindow (Component&)
    {
        //dc = GetDC ((HWND) nativeWindow->getNativeHandle());
    }

    void deleteRenderContext()
    {
        if (renderContext != nullptr)
        {
            wglDeleteContext (renderContext);
            renderContext = nullptr;
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

Window::Window (const std::string& title) :
    pimpl (new Pimpl (title, pixelFormat))
{
}

Window::~Window()
{
    delete pimpl;
    pimpl = nullptr;
}

void Window::setTitle (const std::string& title)
{
    pimpl->setTitle (title);
}

void Window::update()
{
    pimpl->update();
}

void Window::draw()
{
    pimpl->draw();
}

void* Window::getNativeHandle() const
{
    return pimpl->getNativeHandle();
}

#endif //SQUAREPINE_WINDOWS
