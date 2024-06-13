#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>

int getTextFileContent(char* path, char* buf);
int getFileContentSize(const char* file_name);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
 {
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);

    HANDLE stdHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(stdHandle);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    
    const int FILE_SIZE = 1024;

    OPENFILENAMEA f = { sizeof(OPENFILENAME) };
    f.lpstrFilter = "*.txt";
    f.lpstrTitle = "Pick a txt, nigga";
    f.hwndOwner = NULL;

    char buf[FILE_SIZE] = {};
    f.nMaxFile = sizeof(buf);
    f.lpstrFile = buf;

    bool suc = GetOpenFileNameA(&f);


    char* result_buf = (char*)calloc(FILE_SIZE,sizeof(char));
   
    if (result_buf == NULL) {
        MessageBoxA(NULL, "Couldn't allocate buffer", "Error", MB_ICONERROR);
        return 0;
    }

    getTextFileContent(f.lpstrFile, result_buf);

    DWORD written;
    char msg[] = "Contents of the message:";
    WriteConsoleOutputCharacterA(h, msg,sizeof(msg), {0,1}, &written);
    WriteConsoleOutputCharacterA(h, result_buf, getFileContentSize(f.lpstrFile), { 0,2 }, &written);
    free(result_buf);
    scanf("%d");
}

int getTextFileContent(char* path,char* buf) {
    FILE* file = NULL;
    if ((file = fopen(path, "r")) == NULL) {
        MessageBoxA(NULL, "Couldn't open the file", "Error", MB_ICONERROR);
        return 0;
    }

    int i;
    for (i = 0; !feof(file); i++) {
        buf[i] = fgetc(file);
    }

    fclose(file);
    return i;
}

int getFileContentSize(const char* file_name) {
    FILE* file = fopen(file_name,"r");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);
    return size;
}
