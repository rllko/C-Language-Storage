// dllmain.cpp : Defines the entry point for the DLL application

#include <Windows.h>
#include <stdio.h>
#include <wincontypes.h>
#include <vadefs.h>
#include <minwinbase.h>
#include <processenv.h>
#include <libloaderapi.h>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <consoleapi2.h>
#include <consoleapi.h>
#include <vadefs.h>
#include "codecave.h"

#include "tools.h"
#include "structs and globals.h"
#include <malloc.h>
#include "features.h"

void createWindow() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Ev1l-W4re");
}

DWORD WINAPI HackThread(HMODULE hModule) {
	createWindow();
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// setup text variables
	COORD yaw_text =
		createTextLine(hOut, "Mouse Yaw :");
	COORD pitch_text =
		createTextLine(hOut, "Mouse Pitch :");
	COORD x_coord_text =
		createTextLine(hOut, "X:");
	COORD y_coord_text =
		createTextLine(hOut, "Y:");
	COORD z_coord_text =
		createTextLine(hOut, "Z:");
	COORD closest_enemy_name_text =
		createTextLine(hOut, "Closest Enemy:");
	COORD closest_enemy_distance_text =
		createTextLine(hOut, "Enemy Distance:");
	COORD speed_text =
		createTextLine(hOut, "Fly Speed:");
	COORD line_text =
		createTextLine(hOut, "==================");
	COORD enabled_fly =
		createTextLine(hOut, "[1]Fly:");
	COORD enabled_aimbot =
		createTextLine(hOut, "[2]Aimbot:");

	//setup global variables
	myself = (Entity*)calloc(1, sizeof(Entity));
	baseAddress = (uintptr_t)getBaseAddress();

	setCodeCave((uintptr_t*)(baseAddress + 0xC123A), get_enemy_information, 0);
	setCodeCave((uintptr_t*)(baseAddress + 0xC2D5A), get_localplayer_information, 0);

	// setup player Amount
	uintptr_t* playerAmount = (uintptr_t*)(baseAddress + 0x18AC0C);

	// Aimbot
	int aimbotEnabled = 0;

	// Fly
	uintptr_t* flyPatchAdress = (uintptr_t*)(baseAddress + 0xC0A10);
	int flyEnabled = 0;
	float flySpeed = 0.01f;
	BYTE flyPatchByte[2] = { 0x7f,0x14 };

	while (1) {

		if (GetAsyncKeyState('1') & 0x1) {
			flyEnabled = !flyEnabled;
			flyPatchByte[0] = flyEnabled ? 0x7c : 0x7f;
			writeBytes(flyPatchAdress, (BYTE*)flyPatchByte, 1);
		}

		if (GetAsyncKeyState('2') & 0x1) {
			aimbotEnabled = !aimbotEnabled;
		}

		if (GetAsyncKeyState(VK_UP) & 0xb1) {
			flySpeed += 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0xb1) {
			flySpeed -= 0.01f;
		}

		if (aimbotEnabled) {
			if (*playerAmount)
				applyAimbot(*playerAmount);
		}

		if (flyEnabled) {
			fly(flySpeed);
		}

		if (myself == NULL)
			return 1;

		SetConsoleCursorPosition(hOut, pitch_text);
		printf("%.2f", myself->pitch);
		SetConsoleCursorPosition(hOut, yaw_text);
		printf("%.2f", myself->yaw);
		SetConsoleCursorPosition(hOut, x_coord_text);
		printf("%.2f", myself->body.x);
		SetConsoleCursorPosition(hOut, y_coord_text);
		printf("%.2f", myself->body.y);
		SetConsoleCursorPosition(hOut, z_coord_text);
		printf("%.2f", myself->body.z);
		SetConsoleCursorPosition(hOut, speed_text);
		printf("%.2f", flySpeed);
		SetConsoleCursorPosition(hOut, line_text);
		printf("");

		SetConsoleCursorPosition(hOut, enabled_fly);
		printf("%s", flyEnabled ? "ON " : "OFF");

		SetConsoleCursorPosition(hOut, enabled_aimbot);
		printf("%s", aimbotEnabled ? "ON " : "OFF");

		if (closestEntity.entity == NULL)
			continue;

		SetConsoleCursorPosition(hOut, closest_enemy_name_text);
		printf("%s", closestEntity.entity->name);
		SetConsoleCursorPosition(hOut, closest_enemy_distance_text);
		printf("%.2f", closestEntity.distanceFromMe);
	}

	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	HANDLE hThread;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL);
		if (hThread) {
			CloseHandle(hThread);
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

