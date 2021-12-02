#include "common.h"
#define PORT_NUM      10200
#define MAX_MSG_LEN   256
#define SERVER_IP     "192.168.153.1"//서버 IP 주소

void RecvThreadPoint(void* param);
int count = 0;
int count2 = 20;
int main()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
    {
        return -1;
    }

    SOCKADDR_IN servaddr = { 0 };//소켓 주소
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    servaddr.sin_port = htons(PORT_NUM);

    int re = 0;
    re = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));//연결 요청
    if (re == -1)
    {
        return -1;
    }
    _beginthread(RecvThreadPoint, 0, (void*)sock);
    int count = 1;
    char nickname[MAX_MSG_LEN] = "";
    char msg[MAX_MSG_LEN] = "";
    while (true)
    {
        Sleep(1);
        gotoxy(45, count2 - 1);
        gotoxy(50, count2);
        printf("입력 : ");
        gets_s(msg, MAX_MSG_LEN);       //입력
        send(sock, msg, sizeof(msg), 0);//송신
        if (strcmp(msg, "exit") == 0)
        {
            break;
        }
    }
    closesocket(sock);  

    WSACleanup();
    return 0;
}
void RecvThreadPoint(void* param)
{
    SOCKET sock = (SOCKET)param;
    char msg[MAX_MSG_LEN];

    SOCKADDR_IN cliaddr = { 0 };
    int len = sizeof(cliaddr);

    while (recv(sock, msg, MAX_MSG_LEN, 0) > 0)
    {
        gotoxy(0, count);
        printf("%s\n", msg);            //출력
        count++;
        gotoxy(50, count2);
        printf("                          ");
        if (count >= 30)
            count2++;
        gotoxy(50, count2);
    }
    closesocket(sock);
}