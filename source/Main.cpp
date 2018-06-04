#include "Module.h"

#if SQUAREPINE_WINDOWS
    #include <Windows.h>
#endif

using namespace squarepine;

//==============================================================================
/**
    https://github.com/WeAreROLI/JUCE/blob/develop/modules/juce_gui_basics/native/juce_win32_Windowing.cpp

*/

//==============================================================================
#if _WINDOWS && (_WIN32 || _WIN64)

#if __cplusplus_winrt

#else

LRESULT CALLBACK updateWindowProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            if (GetDC (hWnd) == nullptr)
                return -1;
        break;

        case WM_PAINT:
        {
            static TCHAR greeting[] = _T ("Hello, World!");

            PAINTSTRUCT ps;
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

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Colour colour = Colours::black;
    (void) colour;
    OpenGLContext contextasdf;
    (void) contextasdf;
    Window windowasdf;
    (void) windowasdf;

    static TCHAR szWindowClass[]        = _T ("win32app");
    static TCHAR windowsTitle[]         = _T ("Win32 Guided Tour Application");
    static HINSTANCE handleInstance     = nullptr;

    WNDCLASSEX wcex = { 0 };

    wcex.cbSize         = sizeof (wcex);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = updateWindowProcedure;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon (hInstance, MAKEINTRESOURCE (IDI_APPLICATION));
    wcex.hCursor        = LoadCursor (nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH) (COLOR_WINDOW + 1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon (wcex.hInstance, MAKEINTRESOURCE (IDI_APPLICATION));

    if (! RegisterClassEx (&wcex))
    {
        return 1;
    }

    handleInstance = hInstance;

    HWND windowHandle = CreateWindow (szWindowClass, windowsTitle,
                                      WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                      800, 600,
                                      nullptr, nullptr, hInstance, nullptr);

    if (windowHandle == nullptr)
    {
        return 1;
    }

    ShowWindow (windowHandle, nCmdShow);
    UpdateWindow (windowHandle);

    MSG message;
    while (GetMessage (&message, nullptr, 0, 0) != FALSE)
    {
        TranslateMessage (&message);
        DispatchMessage (&message);
    }

    return (int) message.wParam;
}
#endif //Windows, not UWP

#else

int main()
{
    return 0;
}

#endif
