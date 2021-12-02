#include "common.h"

IN_ADDR GetDefaultMyIP() {
	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };
	if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR) {
		return addr;
	}
	HOSTENT* ptr = gethostbyname(localhostname);
	while (ptr && ptr -> h_name) {
		if (ptr->h_addrtype == PF_INET) {
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
			break;
		}
		ptr++;
	}
	return addr;
}

void Remove(char* a, char* b) {
	int len;
	char* p_pos;

	while (*a) {
		if (*a++ == *b) {
			for (len = 1; *(b + len); len++) {
				if (*a++ != *(b + len)) break;
			}
			if (*(b + len) == 0) {
				a -= len;
				for (p_pos = a; *(p_pos + len); p_pos++) *p_pos = *(p_pos + len);
				*p_pos = 0;
			}
		}
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}