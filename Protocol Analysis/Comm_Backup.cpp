#include "Comm.h"

void serverTCP(HWND winhandle) {
    SOCKET sd, new_sd;
    struct sockaddr_in server, client;
    WSADATA wsaData;
    int client_len, bytes_to_read, n;
    char *bp, buf[BUFSIZE];

    if (sd = socket(AF_INET, SOCK_STREAM, 0) == -1) {
        OutputDebugString("Error");
        return;
    }

    WSAAsyncSelect(sd, winhandle, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

    memset((char *)&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(getPort());
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        OutputDebugString("Error");
        return;
    }

    listen(sd, 5);
    /*
    while (TRUE) {
        client_len = sizeof(client);
        if ((new_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1) {
            OutputDebugString("Error");
            return;
        }
        fprintf(stderr, "Remote Address: %s\n", inet_ntoa(client.sin_addr));
        bp = buf;
        bytes_to_read = BUFSIZE;
        while ((n = recv(new_sd, bp, bytes_to_read, 0)) < BUFSIZE) {
            bp += n;
            bytes_to_read -= n;
            if (n == 0)
                break;
        }
    }
    */
    closesocket(sd);
    WSACleanup();
}

void serverUDP(HWND winhandle) {
    SOCKET sd;
    struct sockaddr_in server, client;
    WSADATA wsaData;
    int client_len, n;
    char *buf;


    if ((sd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        OutputDebugString("Error");
        return;
    }

    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(getPort());
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        OutputDebugString("Error");
        return;
    }

    while (TRUE) {
        client_len = sizeof(client);
        if ((n = recvfrom(sd, buf, MAXBUF, 0, (struct sockaddr *)&client, &client_len)) < 0) {
            OutputDebugString("Error");
            return;
        }
    }

    closesocket(sd);
    WSACleanup();
}

void clientTCP(HWND winhandle) {
    SOCKET sd;
    struct hostent *hp;
    struct sockaddr_in server;
    struct in_addr *addr_p, my_addr;
    char buf[BUFSIZE], **pptr, ip_address[MAXBUF];
    int ns, port;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        OutputDebugString("Error");
        return;
    }

    memset((char *)&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(getPort());

    addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
    addr_p = &my_addr;

    if (isdigit(*getIPHost())) {
        if ((port = inet_addr(getIPHost())) == 0) {
            OutputDebugString("Error");
            return;
        }
        strcpy_s(ip_address, getIPHost());
        addr_p->s_addr = inet_addr(ip_address);

        if (hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof(my_addr))) {
            OutputDebugString("Error");
            return;
        }
    }
    else {
        if ((hp = gethostbyname(getIPHost())) == NULL) {
            OutputDebugString("Error");
            return;
        }
    }

    memcpy((char *)&server.sin_addr, hp->h_addr, hp->h_length);

    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        OutputDebugString("Error");
        return;
    }

    pptr = hp->h_addr_list;
    memset((char *)buf, 0, sizeof(buf));
    // fgets(stdin, buf); // definitely change this

    ns = send(sd, buf, BUFSIZE, 0);

    closesocket(sd);
    WSACleanup();
}

void clientUDP(HWND winhandle) {
    SOCKET sd;
    struct hostent *hp;
    struct sockaddr_in server, client;
    struct in_addr *addr_p, my_addr;
    WSADATA wsaDATA;
    int server_len, client_len, data_size, port;
    char buf[MAXBUF], ip_address[MAXBUF];

    if ((sd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        OutputDebugString("Error");
        return;
    }

    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(getPort());

    addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
    addr_p = &my_addr;

    if (isdigit(*getIPHost())) {
        if ((port = inet_addr(getIPHost())) == 0) {
            OutputDebugString("Error");
            return;
        }
        strcpy_s(ip_address, getIPHost());
        addr_p->s_addr = inet_addr(ip_address);

        if (hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof(my_addr))) {
            OutputDebugString("Error");
            return;
        }
    }
    else {
        if ((hp = gethostbyname(getIPHost())) == NULL) {
            OutputDebugString("Error");
            return;
        }
    }

    memcpy((char *)&server.sin_addr, hp->h_addr, hp->h_length);

    memset((char *)&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(0);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr *)&client, sizeof(client)) == -1) {
        OutputDebugString("Error");
        return;
    }

    client_len = sizeof(client);

    if (getsockname(sd, (struct sockaddr *)&client, &client_len)) {
        OutputDebugString("Error");
        return;
    }

    server_len = sizeof(server);

    if (sendto(sd, buf, data_size, 0, (struct sockaddr *)&server, server_len) == -1) {
        OutputDebugString("Error");
        return;
    }
}
