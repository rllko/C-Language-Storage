#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <consoleapi2.h>
#include <libloaderapi.h>
#include <memoryapi.h>
#include <wincontypes.h>
#include <vadefs.h>



uintptr_t getBaseAddress() {
	return (uintptr_t)GetModuleHandle(NULL);
}

void protectedRead(void* dest, void* src, int len) {
	DWORD old;
	VirtualProtect(dest, sizeof(dest), PAGE_EXECUTE_READWRITE, &old);
	memcpy(dest, src, len);
	VirtualProtect(dest, sizeof(dest), old, &old);
}

void readBytes(void* address, void* buffer, int len) {
	protectedRead(buffer, address, len);
}

void writeBytes(void* destAddress, void* patch, int len) {
	protectedRead(destAddress, patch, len);
}


COORD createTextLine(HANDLE hOut, const char* text) {
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(hOut, &ci);
	ci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &ci);
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hOut, &csbi);
	csbi.dwCursorPosition;

	const char* displayMessage = text;
	COORD displayMessageCoord = { 0, csbi.dwCursorPosition.Y + 1 };

	SetConsoleCursorPosition(hOut, displayMessageCoord);
	printf(displayMessage);

	COORD displayNumbersCoord = { (short)strlen(text) + 1, displayMessageCoord.Y };
	COORD next = { 0, csbi.dwCursorPosition.Y + 1 };
	SetConsoleCursorPosition(hOut, next);
	SetConsoleTextAttribute(hOut, 0x7);
	return displayNumbersCoord;
}