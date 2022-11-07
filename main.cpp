#ifndef UNICODE
#define UNICODE
#endif

#include <bitset>
#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <CommCtrl.h>
// #include <winuser.h>
// #include <components.h>
// #include <wingdi.h>
// #include <windef.h>
// #include <gdi32lib.h>

// Child Window/Control IDs
#define IDC_BUTTON01 101
#define IDC_TEXTBOX01 102

// Global
HINSTANCE hInstance;
HWND hTextBox01;
HWND hButton01;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void ChangeWindowSize(HWND hWnd, int x, int y, int width, int height);
// OrganiseButtons(HWND parent);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    ::hInstance = hInstance;
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {0};
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // initialize GDI++
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wc.lpfnWndProc = WindowProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Create the window.

    HWND hWnd = CreateWindowEx(
        0,                           // Optional window styles.
        CLASS_NAME,                  // Window class
        L"Learn to Program Windows", // Window text
        WS_OVERLAPPEDWINDOW,         // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,      // Parent window
        NULL,      // Menu
        hInstance, // Instance handle
        NULL       // Additional application data
    );

    if (hWnd == NULL)
    {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // UINT uID = LOWORD(wParam), uCmd = HIWORD(wParam);
    // static HWND hTextBox1;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        RECT rectMainWndClientArea;
        GetClientRect(hWnd, &rectMainWndClientArea);
        int WndWidth = rectMainWndClientArea.right - rectMainWndClientArea.left;
        int WndHeight = rectMainWndClientArea.bottom - rectMainWndClientArea.top;
        std::cout << "width:" << WndWidth << "    Height: " << WndHeight << std::endl;

        ::hTextBox01 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"Nothing happened yet",
                                      ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | ES_NOHIDESEL | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
                                      10, 10, WndWidth - 20, WndHeight - 200, hWnd, (HMENU)IDC_TEXTBOX01, ::hInstance, NULL);
        ::hButton01 = CreateWindowEx(0L, WC_BUTTON, L"Button 1",
                                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                     10, WndHeight - 50, 150, 50, hWnd, (HMENU)IDC_BUTTON01, ::hInstance, NULL);
    }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        // FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        HBRUSH brush = CreateSolidBrush(0xa0a0a0);
        HBRUSH brush2 = CreateSolidBrush(0x0000ff);

        FillRect(hdc, &ps.rcPaint, brush);

        Gdiplus::Graphics gf(hdc);
        // Gdiplus::Pen pen1(Gdiplus::Color(50, 0, 50), 1.0F);
        Gdiplus::Pen pen1(Gdiplus::Color(255, 0, 0, 255), 3);
        Gdiplus::Pen pen2(Gdiplus::Color(50, 0, 50), 1.0F);

        // std::cout << "hdc : " << std::hex << (UINT64)hdc << std::endl;
        // std::cout << "gf : " << std::hex << (UINT64)&gf << std::endl;

        // std::cout << "pen1 : " << std::hex << (UINT64)&pen1 << std::endl;
        // std::cout << "draw line" << std::endl;

        gf.DrawLine(&pen1, 0, 0, 100, 100);
        gf.DrawLine(&pen1, 30, 30, 500, 300);
        gf.DrawLine(&pen1, 500, 500, 1200, 500);
        gf.DrawPie(&pen2, 100, 100, 50, 50, 90, 170);

        // PAINTSTRUCT ps1;
        // HDC hdc1 = GetDC(hTextBox1);
        // Gdiplus::Graphics gt(hdc1);
        // gt.DrawLine(&pen1, 0, 0, 300, 300);
        // gf.DrawLine(&pen1, 10, 10, 20, 20);

        // Gdiplus::Graphics gf(hdc);
        // Gdiplus::Pen pen1(Gdiplus::Color(255, 0, 0));
        // gf.draw

        EndPaint(hWnd, &ps);

        return 0;
    }
    case WM_COMMAND:
        switch (wParam)
        {
        case MAKELONG(IDC_BUTTON01, BN_CLICKED):
        {
            wchar_t text[500];
            HWND hTextBox1 = GetDlgItem(hWnd, IDC_TEXTBOX01);
            std::cout << "Button was Clicked" << std::endl;
            // SendMessage(GetDlgItem(hWnd, IDC_TEXTBOX01), EM_UNDO, 0, 0);
            // GetWindowText(hTextBox1, text, GetWindowTextLength(hTextBox1));
            // SetWindowText(hTextBox1, L"This is the toolbox text");
            std::wcout << L"text is: " << text << std::endl;
            ChangeWindowSize(::hTextBox01, 20, 20, 100, 100);
            return 0;
        }
        case MAKELONG(IDC_TEXTBOX01, EN_CHANGE):
        {
            std::cout << "Text Box was clicked" << std::endl;
            return 0;
        }
        }

        return 0;

    case WM_ACTIVATE:

        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void ChangeWindowSize(HWND hWnd, int x, int y, int width, int height)
{
    // function resizes window for the given hWnd
    // if input x, y, width, height = -1; that dimension is not to be changed;
    RECT tempRect;
    int tempX, tempY;
    HWND hParent = GetParent(hWnd);
    GetWindowRect(hWnd, &tempRect);
    POINT p = {tempRect.left, tempRect.top};
    ScreenToClient(hParent, &p);
    tempX = p.x;
    tempY = p.y;

    if (x < 0)
    {
        x = tempX;
    };
    if (y < 0)
    {
        y = tempY;
    };
    if (width < 0)
    {
        width = tempRect.right - tempRect.left;
    };
    if (height < 0)
    {
        height = tempRect.bottom - tempRect.top;
    };
    std::cout << "window x: " << x << ", window y: " << y << ", window width: " << width << ", window height: " << height << std::endl;
    SetWindowPos(hWnd, NULL, x, y, width, height, 0);
    return;
}