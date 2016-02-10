/******************************************************************************
Source File: Comm.h
Program: Protocol Analysis
Functions:
Date: February 9, 2016
Revisions:
    February 9, 2016 - Implemented the basic TCP server and client functions. 
    February 10, 2016 - Implemented the basic UDP server and client functions.
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
#include "Comm.h"
#include "GUI.h"

#define BUFSIZE 255

void serverTCP();

void serverUDP();

void clientTCP();

void clientUDP();
