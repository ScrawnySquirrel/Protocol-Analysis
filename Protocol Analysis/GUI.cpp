#include "GUI.h"

// The group window handles
HWND grpSettings, grpProtocol, grpConnection, grpTransfer, grpStatus, grpSent, grpStat;

// The Radio button handles
HWND radioTCP, radioUDP;

// The static label handles
HWND labelIPHost, labelPort, labelFile, labelSize, labelNum;

// The output window handles
HWND lstStat, lstSent, lstStatus;

// The input field handles
HWND inputIPHost, inputPort, inputFile, inputSize, inputNum;

// The button handles
HWND btnStart, btnStop, btnSend, btnReset, btnBrowse, btnResetStat, btnClrSent, btnClrStatus; // First 4 not used!!!

// The counter for list boxes
DWORD cntStatus = 0, cntSent = 0;

// The flag for modes
BYTE mode, protocol;

// The buffer for getting input data
char* buf = (char*)malloc(MAXBUF);

void createSettingElements(HWND handle) {
    grpSettings = CreateWindow("BUTTON", "Settings", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 20, 20, 446, 270, handle, NULL, NULL, NULL);

    grpProtocol = CreateWindow("BUTTON", "Protocol", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 40, 45, 406, 40, handle, NULL, NULL, NULL);
    radioTCP = CreateWindow("BUTTON", "TCP", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 60, 60, 50, 20, handle, (HMENU)RADIOTCP, NULL, NULL);
    radioUDP = CreateWindow("BUTTON", "UDP", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 130, 60, 50, 20, handle, (HMENU)RADIOUDP, NULL, NULL);

    grpConnection = CreateWindow("BUTTON", "Connection Settings", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 40, 90, 406, 80, handle, NULL, NULL, NULL);
    labelIPHost = CreateWindow("STATIC", "IP/Host:", WS_VISIBLE | WS_CHILD, 60, 115, 85, 20, handle, NULL, NULL, NULL);
    inputIPHost = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 145, 115, 281, 20, handle, NULL, NULL, NULL);
    labelPort = CreateWindow("STATIC", "Port:", WS_VISIBLE | WS_CHILD, 60, 140, 85, 20, handle, NULL, NULL, NULL);
    inputPort = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 145, 140, 281, 20, handle, NULL, NULL, NULL);

    grpTransfer = CreateWindow("BUTTON", "Transfer Settings", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 40, 175, 406, 105, handle, NULL, NULL, NULL);
    labelFile = CreateWindow("STATIC", "File:", WS_VISIBLE | WS_CHILD, 60, 200, 85, 20, handle, NULL, NULL, NULL);
    inputFile = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 145, 200, 221, 20, handle, NULL, NULL, NULL);
    btnBrowse = CreateWindow("BUTTON", "Browse", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 200, 60, 20, handle, (HMENU)BUTTONBROWSE, NULL, NULL);
    labelSize = CreateWindow("STATIC", "Packet Size:", WS_VISIBLE | WS_CHILD, 60, 225, 85, 20, handle, NULL, NULL, NULL);
    inputSize = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 145, 225, 281, 20, handle, NULL, NULL, NULL);
    labelNum = CreateWindow("STATIC", "# of packets:", WS_VISIBLE | WS_CHILD, 60, 250, 85, 20, handle, NULL, NULL, NULL);
    inputNum = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 145, 250, 281, 20, handle, NULL, NULL, NULL);

    mode = CLIENTMODE;
    setMode(mode);

    CheckRadioButton(handle, RADIOTCP, RADIOUDP, RADIOTCP);
    protocol = TCPPROTOCOL;
}

void createStatElements(HWND handle) {
    grpStat = CreateWindow("BUTTON", "Stats", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 486, 20, 294, 270, handle, NULL, NULL, NULL);
    lstStat = CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 506, 40, 254, 210, handle, NULL, NULL, NULL);
    btnResetStat = CreateWindow("BUTTON", "Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 700, 260, 60, 20, handle, (HMENU)BUTTONRESETSTAT, NULL, NULL);
}

void createSentElements(HWND handle) {
    grpSent = CreateWindow("BUTTON", "Data Sent", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 20, 310, 446, 270, handle, NULL, NULL, NULL);
    lstSent = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_DISABLENOSCROLL, 40, 330, 406, 210, handle, NULL, NULL, NULL);
    btnClrSent = CreateWindow("BUTTON", "Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 386, 550, 60, 20, handle, (HMENU)BUTTONCLEARSENT, NULL, NULL);
}

void createStatusElements(HWND handle) {
    grpStatus = CreateWindow("BUTTON", "Status", WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP, 486, 310, 294, 270, handle, NULL, NULL, NULL); 
    lstStatus = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_DISABLENOSCROLL, 506, 330, 254, 210, handle, NULL, NULL, NULL);
    btnClrStatus = CreateWindow("BUTTON", "Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 700, 550, 60, 20, handle, (HMENU)BUTTONCLEARSTATUS, NULL, NULL);
}

void createGUI(HWND handle) {
    createSettingElements(handle);
    createStatusElements(handle);
    createSentElements(handle);
    createStatElements(handle);
    btnReset = CreateWindow("BUTTON", "Reset", WS_VISIBLE | WS_CHILD | WS_BORDER, 720, 590, 60, 20, handle, (HMENU)BUTTONRESETALL, NULL, NULL);
}

void paintStatus(char *msg) {
    SendMessage(lstStatus, LB_ADDSTRING, cntStatus++, (LPARAM)msg);
}

void paintSent(char *msg) {
    SendMessage(lstSent, LB_ADDSTRING, cntSent++, (LPARAM)msg);
}

void updateStats() {}

void checkProtocol(HWND handle) {
    if (IsDlgButtonChecked(handle, RADIOTCP) == BST_CHECKED) {
        protocol = TCPPROTOCOL;
    } else if (IsDlgButtonChecked(handle, RADIOUDP) == BST_CHECKED) {
        protocol = UDPPROTOCOL;
    }
}

int getWindowState() {
    return protocol;
}

void setMode(DWORD mode) {
    if (mode == SERVERMODE) {
        mode = SERVERMODE;

        EnableWindow(inputIPHost, FALSE);
        EnableWindow(inputSize, FALSE);
        EnableWindow(inputNum, FALSE);
    } else if (mode == CLIENTMODE) {
        mode = CLIENTMODE;

        EnableWindow(inputIPHost, TRUE);
        EnableWindow(inputSize, TRUE);
        EnableWindow(inputNum, TRUE);
    }
}

void clearStatus() {
    SendMessage(lstStatus, LB_RESETCONTENT, 0, 0);
    cntStatus = 0;
}

void clearSent() {
    SendMessage(lstSent, LB_RESETCONTENT, 0, 0);
    cntSent = 0;
}

void resetStat() {}

void resetAll() {
    clearStatus();
    clearSent();
    resetStat();
}

char* getIPHost() {
    memset(buf, 0, MAXBUF);
    if (GetWindowText(inputIPHost, buf, MAXBUF) <= 0)
        return NULL;
    return buf;
}

int getPort() {
    memset(buf, 0, MAXBUF);
    if (GetWindowText(inputPort, buf, MAXBUF) <= 0)
        return NULL;
    return atoi(buf);
}

char* getFile() {
    memset(buf, 0, MAXBUF);
    if (GetWindowText(inputFile, buf, MAXBUF) <= 0)
        return NULL;
    return buf;
}

int getSize() {
    memset(buf, 0, MAXBUF);
    if (GetWindowText(inputSize, buf, MAXBUF) <= 0)
        return NULL;
    return atoi(buf);
}

int getNum() {
    memset(buf, 0, MAXBUF);
    if (GetWindowText(inputNum, buf, MAXBUF) <= 0)
        return NULL;
    return atoi(buf);
}

void setField(HWND handle) {}