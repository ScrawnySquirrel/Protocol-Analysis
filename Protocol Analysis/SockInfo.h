/******************************************************************************
Source File: SockInfo.h
Program: Protocol Analysis
Functions:
Date: February 10, 2016
Revisions:
    February 10, 2016 - File created. Implement sock information functions.
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes:
******************************************************************************/
#pragma once
#pragma comment(lib,"Ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>

#define DATA_BUFSIZE 8192

typedef struct _SOCKET_INFORMATION {
    BOOL RecvPosted;
    CHAR Buffer[DATA_BUFSIZE];
    WSABUF DataBuf;
    SOCKET Socket;
    DWORD BytesSEND;
    DWORD BytesRECV;
    _SOCKET_INFORMATION *Next;
} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

#define WM_SOCKET (WM_USER + 1)

void CreateSocketInformation(SOCKET s);
LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);
void FreeSocketInformation(SOCKET s);
