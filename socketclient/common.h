#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <windows.h>


#pragma comment(lib, "ws2_32")
IN_ADDR GetDefaultMyIP();

void gotoxy(int x, int y);