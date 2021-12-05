#include "common.h"
#define PORT_NUM      10200
#define MAX_MSG_LEN   256
char systemmessage[MAX_MSG_LEN];

void RecvThreadPoint(void* param);
int count = 0;
int count2 = 20;
int main()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    IN_ADDR addr;
    addr = GetDefaultMyIP(); //ip �ҷ�����
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
    {
        return -1;
    }

    SOCKADDR_IN servaddr = { 0 };//���� �ּ�
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(inet_ntoa(addr)); //ip �޾ƿ���
    servaddr.sin_port = htons(PORT_NUM);

    int re = 0;
    re = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));//���� ��û
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
        printf("�Է���... ");
        gets_s(msg, MAX_MSG_LEN);       //�Է�
        send(sock, msg, sizeof(msg), 0);//�۽�
        if (strstr(msg, "/ģ����û") != NULL) {
            gotoxy(0, count);
            count++;
            if (strlen(msg) > 100) {
                count++;
            }
            gotoxy(50, count2);
            printf("                                                                                                                        ");
            if (count >= 30)
                count2++;
            gotoxy(50, count2);
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
        printf("%s\n", msg);            //���
        count++;
        if (strlen(msg) > 100) {
            count++;
        }
        gotoxy(50, count2);
        printf("                                                                                                                        ");
        if (count >= 30)
            count2++;
        gotoxy(50, count2);
    }

    closesocket(sock);
}