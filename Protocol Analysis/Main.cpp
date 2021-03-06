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
    February 10, 2016 - Implement WSA events in WndProc.
    February 11, 2016 - Update WndProc to handle different protocols (TCP/UDP).
    February 12, 2016 - Added events in WndProc for new revamped GUI.
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes: 
******************************************************************************/
#define STRICT

#include "Comm.h"
#include <windows.h>
#include "resource.h"
#include "GUI.h"
#include "SockInfo.h"

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

    hwnd = CreateWindow(Name, Name, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 815, 680, 
        NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    SOCKET sd;
    LPSOCKET_INFORMATION SocketInfo;
    DWORD RecvBytes;
    DWORD SendBytes;
    DWORD Flags;

    switch (Message) {
    case WM_CREATE:
        createGUI(hwnd);
        fprintf(stdout, "Hello world");
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_FILE_EXIT:
            PostQuitMessage(0);
            break;
        case ID_MODE_SERVER:
            setMode(SERVERMODE);
            break;
        case ID_MODE_CLIENT:
            setMode(CLIENTMODE);
            break;
        case ID_ABOUT_USERGUIDE:
            break;
        case RADIOTCP:
        case RADIOUDP:
            checkProtocol(hwnd);
            MessageBox(hwnd, "WindowSockets", "Radio", MB_OK);
            break;
        case BUTTONBROWSE:
            MessageBox(hwnd, "WindowSockets", "Browse", MB_OK);
            break;
        case BUTTONCLEARSTATUS:
            MessageBox(hwnd, "WindowSockets", "Clear Status", MB_OK);
            break;
        case BUTTONCLEARSENT:
            MessageBox(hwnd, "WindowSockets", "Clear Sent", MB_OK);
            break;
        case BUTTONRESETSTAT:
            MessageBox(hwnd, "WindowSockets", "Clear Stat", MB_OK);
            break;
        case BUTTONRESETALL:
            MessageBox(hwnd, "WindowSockets", "Reset All", MB_OK);
            break;
        }
        break;
    case WM_SOCKET:
        if (WSAGETSELECTERROR(lParam)) {
            printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
            FreeSocketInformation(wParam);
        } else {
            switch (WSAGETSELECTEVENT(lParam)) {
            case FD_CONNECT:
                break;
            case FD_ACCEPT:
                if ((sd = accept(wParam, NULL, NULL)) == INVALID_SOCKET) {
                    paintStatus("Error: accept - INVALID SOCKET");
                    exit(1);
                }
                CreateSocketInformation(sd);
                WSAAsyncSelect(sd, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
                break;
            case FD_READ:
                if (getWindowState() == TCPPROTOCOL) {
                } else if (getWindowState() == UDPPROTOCOL) {
                } else {
                    OutputDebugString("Error: Invalid mode");
                    exit(1);
                }
                break;
            case FD_WRITE:
                if (getWindowState() == TCPPROTOCOL) {
                } else if (getWindowState() == UDPPROTOCOL) {
                } else {
                    OutputDebugString("Error: Invalid mode");
                    exit(1);
                }
                break;
            case FD_CLOSE:
                closesocket((SOCKET)wParam);
                break;
            }
        }
        break;
    case WM_DESTROY:	// Terminate program
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}