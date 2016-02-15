/******************************************************************************
Source File: GUI.h
Program: Protocol Analysis
Functions: 
Date: February 6, 2016
Revisions: 
    February 6, 2016 - Implement basic function to create UI elements. Create
        simple getters and setters for input fields.
    February 9, 2016 - Implement more specific getters. Create getters for each
        input fields. 
    February 11, 2016 - Implement function to retrieve which radio button is 
        selected.
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes:
******************************************************************************/
#pragma once
#include <Windows.h>

#define MAXBUF 256
#define RADIOTCP 9001
#define RADIOUDP 9002
#define BUTTONBROWSE 9003
#define BUTTONSTART 9004
#define BUTTONSEND 9005 // Currently not used; no "Send" button
#define BUTTONRESET 9006

void createElements(HWND winhandle);

int getWindowState(HWND handle);

void setWindowState(HWND handle);

LPSTR getInputText(HWND inputfield);

BOOLEAN setInputText(HWND inputfield, LPSTR text); // When invalid input is detected, default it to base value

LPSTR getIPHost();

DWORD getPort();

LPSTR getFile();

DWORD getSize();

DWORD getNum();
