#pragma once
#include <Windows.h>
#include "tools.h"
#include "structs and globals.h"
#include <malloc.h>
#include <vadefs.h>

void setCodeCave(void* destination, void* patched_function, int mangled_bytes) {
	// size of the jump instruction
	int jmp_length = 5;
	int patch_length = jmp_length + mangled_bytes;
	uintptr_t offset = (uintptr_t)patched_function - (uintptr_t)destination - jmp_length;
	BYTE* patch = (BYTE*)malloc(sizeof(BYTE) * patch_length);

	if (patch == NULL)
		return;

	memset(patch, 0x90, patch_length);
	// e8 = call ; e9 = jmp
	patch[0] = 0xe8;
	memcpy(patch + 1, &offset, jmp_length);
	writeBytes(destination, patch, patch_length);
}

const __declspec(naked) void get_localplayer_information() {
	static uintptr_t returnAddress;
	// can also pop eax and jump to eax instead of creating stack frame
	__asm {
		pop eax
		; store used registers
		; push esi

		mov[myself], esi
		;  mov[esi + 65], al
		;  mov eax, [esi]
		;  mov[playerList], eax

		; pop them back
		; pop esi
		; push returnAddress
		jmp eax
	}

}

const __declspec(naked) void get_enemy_information() {
	static uintptr_t returnAddress;

	__asm {
		mov[playerList], eax
		mov edx, [eax + esi * 4]
		test edx, edx
		retn
	}

}