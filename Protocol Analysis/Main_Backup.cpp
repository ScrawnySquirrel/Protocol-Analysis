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
    SOCKET sd;
    LPSOCKET_INFORMATION SocketInfo;
    DWORD RecvBytes, SendBytes;
    DWORD Flags;

    switch (Message) {
    case WM_CREATE:
        createElements(hwnd);
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
                    break;
                }

                CreateSocketInformation(sd);
                
                WSAAsyncSelect(sd, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
                break;
            case FD_READ:
                SocketInfo = GetSocketInformation(wParam);

                // Read data only if the receive buffer is empty.

                if (SocketInfo->BytesRECV != 0) {
                    SocketInfo->RecvPosted = TRUE;
                    return 0;
                } else {
                    SocketInfo->DataBuf.buf = SocketInfo->Buffer;
                    SocketInfo->DataBuf.len = DATA_BUFSIZE;

                    Flags = 0;
                    if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes,
                        &Flags, NULL, NULL) == SOCKET_ERROR) {
                        if (WSAGetLastError() != WSAEWOULDBLOCK) {
                            printf("WSARecv() failed with error %d\n", WSAGetLastError());
                            FreeSocketInformation(wParam);
                            return 0;
                        }
                    } else { // No error so update the byte count
                        SocketInfo->BytesRECV = RecvBytes;
                    }
                    break;
                }
                break;
            case FD_WRITE:
                SocketInfo = GetSocketInformation(wParam);

                if (SocketInfo->BytesRECV > SocketInfo->BytesSEND) {
                    SocketInfo->DataBuf.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;
                    SocketInfo->DataBuf.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;

                    if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0,
                        NULL, NULL) == SOCKET_ERROR) {
                        if (WSAGetLastError() != WSAEWOULDBLOCK) {
                            printf("WSASend() failed with error %d\n", WSAGetLastError());
                            FreeSocketInformation(wParam);
                            return 0;
                        }
                    }
                    else { // No error so update the byte count
                        SocketInfo->BytesSEND += SendBytes;
                    }
                }

                if (SocketInfo->BytesSEND == SocketInfo->BytesRECV) {
                    SocketInfo->BytesSEND = 0;
                    SocketInfo->BytesRECV = 0;

                    // If a RECV occurred during our SENDs then we need to post an FD_READ
                    // notification on the socket.

                    if (SocketInfo->RecvPosted == TRUE) {
                        SocketInfo->RecvPosted = FALSE;
                        PostMessage(hwnd, WM_SOCKET, wParam, FD_READ);
                    }
                }
                break;
            case FD_CLOSE:
                printf("Closing socket %d\n", wParam);
                FreeSocketInformation(wParam);
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