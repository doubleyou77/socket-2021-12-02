#include "common.h"

IN_ADDR GetDefaultMyIP() {
	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };
	if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR) {
		return addr;
	}
	HOSTENT* ptr = gethostbyname(localhostname);
	while (ptr && ptr->h_name) {
		if (ptr->h_addrtype == PF_INET) {
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
			break;
		}
		ptr++;
	}
	return addr;
}

void Eliminate(char* str, char ch)
{
	int len = strlen(str) + 1;
	for (; *str != '\0'; str++, len--)//���� ���ڸ� ���� ������ �ݺ�
	{
		if (*str == ch)//ch�� ���� ������ ��
		{
			strcpy_s(str, len, str + 1);
			str--;
		}
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}