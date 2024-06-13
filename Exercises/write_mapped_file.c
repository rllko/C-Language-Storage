#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>

int main()
{
	HANDLE hFile = CreateFile(L"test.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBoxA(NULL, "ERROR", "Couldn't open the file", MB_ICONWARNING);
		CloseHandle(hFile);
		return 1;
	}
	const int size = 200;
	HANDLE fileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, size, NULL);

	if (fileMapping == NULL) {
		printf("error number %d. \n", GetLastError());
		MessageBoxA(NULL, "ERROR", "Couldn't Map the file", MB_ICONWARNING);
		CloseHandle(hFile);
		return 2;
	}

	char* data = (char*)MapViewOfFile(fileMapping, FILE_MAP_ALL_ACCESS, 0, 0, size);
	memset(data, NULL, size);
	
	while(true){
		if (GetAsyncKeyState(VK_SPACE))
			break;
		fgets(data, size, stdin);
		printf("%s data sent!", data);
	}

	UnmapViewOfFile(fileMapping);
	CloseHandle(hFile);
	return 0;
}
