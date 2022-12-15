#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 
#define  PORT_NUM (8888)
#define SERVER "192.168.0.1"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <string>

using namespace std;


int main()
{
    WSADATA wsaData;
    WORD    DLLVersion;
    DLLVersion = MAKEWORD(2, 1);//winsocket-dll version


    // �� WSAStartup �}�l Winsocket-DLL
    int err = WSAStartup(DLLVersion, &wsaData);
    if (err != 0)
    {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 1)
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 1;
    }
    else
    {
        printf("The Winsock 2.1 dll was found okay\n");
    }


    SOCKADDR_IN    addr;
    int addrlen = sizeof(addr);

    // Create socket
    SOCKET sListen;        //listening for an incoming connection
    SOCKET sConnection;        //oerating if a connection was found

    // AF_INET        :  ���ܫإߪ�Socket�ݩ�internet family
    // SOCK_STREAM    :  ���ܫإߪ�socket�Oconnection-oriented socket
    sConnection = socket(AF_INET, SOCK_STREAM, NULL);

    // �]�w��}��T�����
    addr.sin_addr.s_addr = inet_addr("192.168.1.110");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_NUM);


    // �]�wListen
    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    if (sListen == INVALID_SOCKET)
    {
        printf("socket function failed with error : %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    // Bind the socket
    int iResult = bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    if (iResult == SOCKET_ERROR)
    {
        printf("Bind failed with error : %u \n", WSAGetLastError());
        closesocket(sListen);
        WSACleanup();
        return 1;
    }
    //SOMAXCONN: listening without any limit
    if (listen(sListen, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("listen function failed with error: %d \n", WSAGetLastError());
        closesocket(sListen);
        WSACleanup();
        return 1;

    }
    else
        printf("Listening on socket...\n");


    // ���ݳs�u
    SOCKADDR_IN clientAddr;
    while (1)
    {
        cout << "Waitting for connect... " << endl;
        if (sConnection = accept(sListen, (SOCKADDR*)&clientAddr, &addrlen))
        {
            cout << "a connection was found." << endl;
            printf("Server : got a connection from : %s\n", inet_ntoa(addr.sin_addr));

            //Send message to client 
            char sendbuf[30] = "sending data test!! >_<";
            while (cin >> sendbuf)
            {
                iResult = send(sConnection, sendbuf, (int)strlen(sendbuf), 0);
                if (iResult == SOCKET_ERROR)
                {

                    printf("send failed with error :%d \n", WSAGetLastError());
                    closesocket(sConnection);
                    WSACleanup();
                    return 1;
                }
            }


        }
    }

    getchar();
    getchar();
}