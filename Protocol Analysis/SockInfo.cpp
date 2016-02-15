#include "SockInfo.h"

LPSOCKET_INFORMATION SocketInfoList;

void CreateSocketInformation(SOCKET s) {
    LPSOCKET_INFORMATION SI;

    if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR,
        sizeof(SOCKET_INFORMATION))) == NULL) {
        //printf("GlobalAlloc() failed with error %d\n", GetLastError());
        return;
    }

    // Prepare SocketInfo structure for use.

    SI->Socket = s;
    SI->RecvPosted = FALSE;
    SI->BytesSEND = 0;
    SI->BytesRECV = 0;

    SI->Next = SocketInfoList;

    SocketInfoList = SI;
}

LPSOCKET_INFORMATION GetSocketInformation(SOCKET s) {
    SOCKET_INFORMATION *SI = SocketInfoList;

    while (SI) {
        if (SI->Socket == s)
            return SI;

        SI = SI->Next;
    }

    return NULL;
}

void FreeSocketInformation(SOCKET s) {
    SOCKET_INFORMATION *SI = SocketInfoList;
    SOCKET_INFORMATION *PrevSI = NULL;

    while (SI) {
        if (SI->Socket == s) {
            if (PrevSI)
                PrevSI->Next = SI->Next;
            else
                SocketInfoList = SI->Next;

            closesocket(SI->Socket);
            GlobalFree(SI);
            return;
        }

        PrevSI = SI;
        SI = SI->Next;
    }
}
