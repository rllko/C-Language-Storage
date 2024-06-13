// OpenDialogg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <Windows.h>

int main() { 
  SYSTEM_INFO info;
  GetSystemInfo(&info);

  printf("Page size: %d\n", info.dwPageSize);

  int* memory;
  if (!(memory = (int*) 
      VirtualAlloc(
        0,
        200,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE))) 
  {
    return 1;
  }

  memory[1] = 5;
  DWORD old;
  VirtualProtect(memory, 200, PAGE_READONLY, &old);

  printf("%d\n", memory[1]);

  VirtualProtect(memory, 200, old, &old);

  memory[1] = 10;
  printf("%d\n", memory[1]);

  VirtualFree(memory, 0, MEM_RELEASE);
}