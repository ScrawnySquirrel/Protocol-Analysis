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
    February 12, 2016 - Revamp GUI to provide better usage and descriptor 
        windows.
Designer: Gabriel Seonghyoung Lee
Programmer: Gabriel Seonghyoung Lee
Notes:
******************************************************************************/
#pragma once
#include <Windows.h>

#define MAXBUF 256
#define RADIOTCP 5001
#define RADIOUDP 5002
#define BUTTONBROWSE 5003
#define BUTTONCLEARSTATUS 5004
#define BUTTONCLEARSENT 5005
#define BUTTONRESETSTAT 5006
#define BUTTONRESETALL 5007
/*
#define BUTTONSTART 5008
#define BUTTONSTOP 5009
#define BUTTONSEND 5010
*/
#define CLIENTMODE 5011
#define SERVERMODE 5012
#define TCPPROTOCOL 5013
#define UDPPROTOCOL 5014

void createSettingElements(HWND handle);

void createStatusElements(HWND handle);

void createSentElements(HWND handle);

void createStatElements(HWND handle);

void createGUI(HWND handle);

void paintStatus(char *msg);

void paintSent(char *msg);

void updateStats();

void checkProtocol(HWND handle);

int getWindowState();

void setMode(DWORD mode);

void clearStatus();

void clearSent();

void resetStat();

void resetAll();

char* getIPHost();

int getPort();

char* getFile();

int getSize();

int getNum();

void setField(HWND handle);
