/******************************************************************************
Source File: Comm.h
Program: Protocol Analysis
Functions:
Date: February 9, 2016
Revisions:
    February 9, 2016 - Implemented the basic TCP server and client functions. 
    February 10, 2016 - Implemented the basic UDP server and client functions.
    February 11, 2016 - Fix TCP server and client functions to use WSAAsync
        functions.
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes:
******************************************************************************/
#pragma once
#pragma comment(lib,"Ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include "GUI.h"
#include "SockInfo.h"

#define WM_SOCKET (WM_USER + 1)
#define BUFSIZE 255

void acceptConnection(SOCKET connection, SOCKET s, HWND handle);

void serverTCP(HWND winhandle);

void serverUDP(HWND winhandle);

void clientTCP(HWND winhandle);

void clientUDP(HWND winhandle);

void sendTCP();

void sendUDP();

void recvTCP();

void recvUDP();
