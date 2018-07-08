#include "Module.h"

bool shouldDraw = true;

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

		case WM_CLOSE:
			DestroyWindow (hWnd);
            return 0;

        case WM_ACTIVATE:
        {
            // The message WM_ACTIVE is sent whenever the application has focus.
            // For example if the application is minimised then it is not in focus.
            // As the application is not in focus it is pointless wasting clock
            // cycles and graphics hardware to render to what cannot be seen.
            shouldDraw = (BOOL) wParam != FALSE;
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

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    static TCHAR windowClassName[]      = _T ("win32app");
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
    wcex.lpszClassName  = windowClassName;
    wcex.hIconSm        = LoadIcon (wcex.hInstance, MAKEINTRESOURCE (IDI_APPLICATION));

    if (! RegisterClassEx (&wcex))
    {
        return 1;
    }

    handleInstance = hInstance;

    HWND windowHandle = CreateWindow (windowClassName, windowsTitle,
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
    zerostruct (message);

#if 0
    while (GetMessage (&message, nullptr, 0, 0) != FALSE)
    {
        TranslateMessage (&message);
        DispatchMessage (&message);
    }
#else
    bool finished = false;
    while (! finished)
    {
        DWORD currentTick = GetTickCount();
        DWORD endTick = currentTick + (1000 / 60);

        while (currentTick < endTick)
        {
            if (PeekMessage (&message, nullptr, 0, 0, PM_REMOVE) != FALSE)
            {
                if (message.message == WM_QUIT)
                {
                    finished = true;
                    break;
                }
                else
                {
                    TranslateMessage (&message);
                    DispatchMessage (&message);
                }

                currentTick = GetTickCount();
            }
            else
            {
                break;
            }

            //processFrame();
        }
    }
#endif

    UnregisterClass (windowClassName, handleInstance);

    return (int) message.wParam;
}
#endif //Windows, not UWP

#else

int main()
{
    return 0;
}

#endif
