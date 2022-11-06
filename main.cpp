#ifndef UNICODE
#define UNICODE
#endif

#include <bitset>
#include <iostream>
#include <windows.h>
#include <CommCtrl.h>
#include <winuser.h>
#include <components.h>
#include <wingdi.h>
// #include <windef.h>
// #include <gdiplus.h>
// #include <gdi32lib.h>
//#pragma comment(lib, "Gdiplus.lib")

// Child Window/Control IDs
#define IDC_BUTTON1 101
#define IDC_TEXTBOX1 102

// Global
HINSTANCE hInstance;

LRESULT CALLBACK
WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    ::hInstance = hInstance;
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
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

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // UINT uID = LOWORD(wParam), uCmd = HIWORD(wParam);
    switch (uMsg)
    {
    case WM_CREATE:
    {
        std::cout << "WM_Create" << std::endl;
        HWND hButton1 = CreateWindow(L"Button", L"Button 11", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 10, 150, 20, hWnd, (HMENU)IDC_BUTTON1, ::hInstance, NULL);
        HWND hTextBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, NULL, ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | ES_NOHIDESEL | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_VISIBLE, 10, 40, 300, 100, hWnd, (HMENU)IDC_TEXTBOX1, ::hInstance, NULL);
        SetWindowText(hTextBox1, L"Whatever!");
        int size = sizeof(HWND);
        std::cout << std::bitset<8 * sizeof(HWND)>((ULONG64)hTextBox1) << "size of HWND is: " << size << std::endl;
        std::cout << std::hex << "HWND as HEX is: " << ((ULONG64)hTextBox1) << std::endl;
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
        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
        FillRect(hdc, &ps.rcPaint, brush);

        // Gdiplus::Graphics grap(hdc);

        // Gdiplus::Graphics graphics(hdc);
        // Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0));
        // graphics.draw

        EndPaint(hWnd, &ps);

        return 0;
    }
    case WM_COMMAND:
        switch (wParam)
        {
        case MAKELONG(IDC_BUTTON1, BN_CLICKED):
        {
            wchar_t text[500];
            HWND hTextBox1 = GetDlgItem(hWnd, IDC_TEXTBOX1);
            std::cout << "Button was Clicked" << std::endl;
            // SendMessage(GetDlgItem(hWnd, IDC_TEXTBOX1), EM_UNDO, 0, 0);
            GetWindowText(hTextBox1, text, GetWindowTextLength(hTextBox1));
            SetWindowText(hTextBox1, L"This is the toolbox text");
            std::wcout << L"text is: " << text << std::endl;
            return 0;
        }
        case MAKELONG(IDC_TEXTBOX1, EN_CHANGE):
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
