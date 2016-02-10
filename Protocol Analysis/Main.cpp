/******************************************************************************
Source File: 
Program: Protocol Analysis
Functions: 
Date: February 6, 2016
Revisions: 
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes: 
******************************************************************************/

/******************************************************************************
Source File: Main.cpp
Program: Protocol Analysis
Functions:
    int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance, 
        LPSTR lspszCmdParam, int nCmdShow)
    LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, 
        LPARAM lParam)
Date: February 6, 2016
Revisions:
    February 6, 2016 - File created. Implement basic WinMain and
        WndProc functions.
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes: 
******************************************************************************/
#define STRICT

#include <windows.h>
#include "resource.h"
#include "GUI.h"

static TCHAR Name[] = TEXT("Protocol Analysis");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#pragma warning (disable: 4096)

HANDLE hComm;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
    LPSTR lspszCmdParam, int nCmdShow) {
    HWND hwnd;
    MSG Msg;
    WNDCLASSEX Wcl;

    Wcl.cbSize = sizeof(WNDCLASSEX);
    Wcl.style = CS_HREDRAW | CS_VREDRAW;
    Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
    Wcl.hIconSm = NULL; // use small version of large icon
    Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style
    Wcl.lpfnWndProc = WndProc;
    Wcl.hInstance = hInst;
    Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // white background
    Wcl.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // the menu class
    Wcl.lpszClassName = Name;
    Wcl.cbClsExtra = 0;      // no extra memory needed
    Wcl.cbWndExtra = 0;

    if (!RegisterClassEx(&Wcl))
        return 0;

    hwnd = CreateWindow(Name, Name, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
        WS_MINIMIZEBOX | WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
        600, 335, NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
    case WM_CREATE:
        createElements(hwnd);
        break;
    case WM_DESTROY:	// Terminate program
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}