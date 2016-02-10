#include "GUI.h"

HWND inputIP, inputPort, radioTCP, radioUDP, inputFile, btnBrowse, inputSize, inputNum, btnStart, btnSend, btnReset;
HWND labelIP, labelPort, labelRadio, labelFile, labelSize, labelNum;

// Should stop be added for the server? Should the application switch from Start to Send depending on the mode?
void createElements(HWND winhandle) {
    labelIP = CreateWindow("STATIC", "IP/Host:", WS_VISIBLE | WS_CHILD, 20, 20, 85, 20, winhandle, NULL, NULL, NULL);
    inputIP = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 105, 20, 250, 20, winhandle, NULL, NULL, NULL);

    labelPort = CreateWindow("STATIC", "Port:", WS_VISIBLE | WS_CHILD, 20, 50, 85, 15, winhandle, NULL, NULL, NULL);
    inputPort = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 105, 50, 250, 20, winhandle, NULL, NULL, NULL);

    radioTCP = CreateWindow("BUTTON", "TCP", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 400, 20, 50, 20, winhandle, (HMENU)RADIOTCP, NULL, NULL);
    radioUDP = CreateWindow("BUTTON", "UDP", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 400, 50, 50, 20, winhandle, (HMENU)RADIOUDP, NULL, NULL);

    labelFile = CreateWindow("STATIC", "File:", WS_VISIBLE | WS_CHILD, 20, 80, 85, 20, winhandle, NULL, NULL, NULL);
    inputFile = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 105, 80, 250, 20, winhandle, NULL, NULL, NULL);
    btnBrowse = CreateWindow("BUTTON", "Browse", WS_VISIBLE | WS_CHILD | WS_BORDER, 400, 80, 50, 20, winhandle, (HMENU)BUTTONBROWSE, NULL, NULL);

    labelSize = CreateWindow("STATIC", "Packet Size:", WS_VISIBLE | WS_CHILD, 20, 110, 85, 20, winhandle, NULL, NULL, NULL);
    inputSize = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 105, 110, 250, 20, winhandle, NULL, NULL, NULL);

    labelNum = CreateWindow("STATIC", "# of packets:", WS_VISIBLE | WS_CHILD, 20, 140, 85, 20, winhandle, NULL, NULL, NULL);
    inputNum = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 105, 140, 250, 20, winhandle, NULL, NULL, NULL);

    btnStart = CreateWindow("BUTTON", "Start", WS_VISIBLE | WS_CHILD | WS_BORDER, 400, 110, 50, 20, winhandle, (HMENU)BUTTONSTART, NULL, NULL);
    btnReset = CreateWindow("BUTTON", "Reset", WS_VISIBLE | WS_CHILD | WS_BORDER, 400, 140, 50, 20, winhandle, (HMENU)BUTTONRESET, NULL, NULL);

}

void setWindowState(HWND handle) {
    if (IsDlgButtonChecked(handle, RADIOTCP) == BST_CHECKED) {
    }
    else if (IsDlgButtonChecked(handle, RADIOUDP) == BST_CHECKED) {
    }
}

LPSTR getInputText(HWND inputfield) {
    LPSTR input = NULL;
    if (GetWindowText(inputfield, input, MAXBUF) > 0)
        return NULL;
    return input;
}

BOOLEAN setInputText(HWND inputfield, LPSTR text) {
    if (SetWindowText(inputfield, text) == 0)
        return 0;
    return 1;
}


LPSTR getIPHost() {
    LPSTR ipHost = NULL;
    if (GetWindowText(inputIP, ipHost, MAXBUF) <= 0)
        return NULL;
    return ipHost;
}

DWORD getPort() {
    LPSTR input = NULL;
    DWORD port;
    if (GetWindowText(inputPort, input, MAXBUF) <= 0)
        return NULL;
    return port = atoi(input);
}

LPSTR getFile() {
    LPSTR file = NULL;
    if (GetWindowText(inputFile, file, MAXBUF) <= 0)
        return NULL;
    return file;
}

DWORD getSize() {
    LPSTR input = NULL;
    DWORD size;
    if (GetWindowText(inputSize, input, MAXBUF) <= 0)
        return NULL;
    return size = atoi(input);
}

DWORD getNum() {
    LPSTR input = NULL;
    DWORD num;
    if (GetWindowText(inputNum, input, MAXBUF) <= 0)
        return NULL;
    return num = atoi(input);
}
