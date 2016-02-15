#include "Comm.h"

void initializeTCP() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        paintStatus("Error: WSAStartup");
        exit(1);
    }
}
void initializeUDP() {}

/*  
void serverTCP(HWND winhandle) {
    WSADATA wsaData;
    SOCKET sd;
    SOCKADDR_IN inetAddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        paintStatus("Error: WSAStartup");
        exit(1);
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        paintStatus("Error: Invalid socket");
        exit(1);
    }

    inetAddr.sin_family = AF_INET;
    inetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    inetAddr.sin_port = htons(getPort());

    if (bind(sd, (PSOCKADDR)&inetAddr, sizeof(inetAddr)) == SOCKET_ERROR) {
        paintStatus("Error: Failed bind");
        exit(1);
    }

    WSAAsyncSelect(sd, winhandle, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

    if (listen(sd, 5)) {
        paintStatus("Error: Failed listen");
        exit(1);
    }
}

void serverUDP(HWND winhandle) {

}

void clientTCP(HWND winhandle) {
    WSADATA wsaData;
    SOCKET sd;
    struct hostent *host;
    struct in_addr my_addr, *addr_p;
    SOCKADDR_IN inetAddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        OutputDebugString("Error: WSAStartup");
        exit(1);
    }

    if ((sd = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        OutputDebugString("Error: Invalid socket");
        exit(1);
    }

    WSAAsyncSelect(sd, winhandle, WM_SOCKET, FD_READ | FD_CLOSE);

    if (isdigit(*getIPHost())) {
        addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
        addr_p = &my_addr;

        addr_p->s_addr = inet_addr(getIPHost());

        if ((host = gethostbyaddr((char *)addr_p, PF_INET, sizeof(my_addr))) == NULL) {
            OutputDebugString("Error: gethosbyaddr");
            exit(1);
        }
    } else {
        if ((host = gethostbyname(getIPHost())) == NULL) {
            OutputDebugString("Error: gethostbyname");
            exit(1);
        }
    }

    inetAddr.sin_family = AF_INET;
    inetAddr.sin_addr.s_addr = htonl((u_long)host->h_addr);
    inetAddr.sin_port = htons(getPort());

    if (connect(sd, (PSOCKADDR)&inetAddr, sizeof(inetAddr)) == SOCKET_ERROR) {
        OutputDebugString("Error: Failed connect");
        exit(1);
    }
}

void clientUDP(HWND winhandle) {

}

void sendTCP() {
    SocketInfo = GetSocketInformation(wParam);
    if (SocketInfo->BytesRECV > SocketInfo->BytesSEND) {
        SocketInfo->DataBuf.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;
        SocketInfo->DataBuf.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;

        if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR) {
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                printf("WSASend() failed with error %d\n", WSAGetLastError());
                FreeSocketInformation(wParam);
                return 0;
            }
        }
        else { // No error so update the byte count
            printf("WSASend() is OK!\n");
            SocketInfo->BytesSEND += SendBytes;
        }
    }

    if (SocketInfo->BytesSEND == SocketInfo->BytesRECV) {
        SocketInfo->BytesSEND = 0;
        SocketInfo->BytesRECV = 0;
        // If a RECV occurred during our SENDs then we need to post an FD_READ notification on the socket
        if (SocketInfo->RecvPosted == TRUE) {
            SocketInfo->RecvPosted = FALSE;
            PostMessage(hwnd, WM_SOCKET, wParam, FD_READ);
        }
    }
}

void sendUDP();

void recvTCP() {
    SocketInfo = GetSocketInformation(wParam);
    // Read data only if the receive buffer is empty
    if (SocketInfo->BytesRECV != 0) {
        SocketInfo->RecvPosted = TRUE;
        return 0;
    }
    else {
        SocketInfo->DataBuf.buf = SocketInfo->Buffer;
        SocketInfo->DataBuf.len = DATA_BUFSIZE;

        Flags = 0;
        if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR) {
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                printf("WSARecv() failed with error %d\n", WSAGetLastError());
                FreeSocketInformation(wParam);
                return 0;
            }
        }
        else { // No error so update the byte count 
            printf("WSARecv() is OK!\n");
            SocketInfo->BytesRECV = RecvBytes;
        }
    }
}

void recvUDP();
*/