#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "sdf.h"

HANDLE getStdHandle(DWORD nStdHandle)
{
    HANDLE handle = GetStdHandle(nStdHandle);
    if (handle == INVALID_HANDLE_VALUE)
    {
        perror("GetStdHandle");
        exit(EXIT_FAILURE);
    }
    return handle;
}

void get_csbi(CONSOLE_SCREEN_BUFFER_INFO *csbi)
{

    if (GetConsoleScreenBufferInfo(getStdHandle(STD_OUTPUT_HANDLE), csbi) == 0)
    {
        fprintf(stderr, "[Error] GetConsoleScreenBufferInfo: %d", GetLastError);
        exit(EXIT_FAILURE);
    }
}

void disableRawMode()
{
    HANDLE handle = getStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    if (!GetConsoleMode(handle, &mode))
    {
        perror("[disable raw mode] GetConsoleMode");
        exit(EXIT_FAILURE);
    }
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    if (!SetConsoleMode(handle, mode))
    {
        perror("[disable raw mode] SetConsoleMode");
        exit(EXIT_FAILURE);
    }
}

void enableRawMode()
{
    HANDLE handle = getStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    if (!GetConsoleMode(handle, &mode))
    {
        perror("[enabling raw mode] GetConsoleMode");
        exit(EXIT_FAILURE);
    }
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    if (!SetConsoleMode(handle, mode))
    {
        perror("[enabling raw mode] SetConsoleMode");
        exit(EXIT_FAILURE);
    }
}

int main(int, char **)
{
    enableRawMode();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    get_csbi(&csbi);

    char ch;
    while (true)
    {
        ch = getchar();
        if (ch == 'q')
        {
            break;
        }
        else if (ch == 'i')
        {
            system("cls");
            int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            printf("\n");
            printf("{\n");
            printf("    right: %d\n", csbi.srWindow.Right);
            printf("    left: %d\n", csbi.srWindow.Left);
            printf("    bottom: %d\n", csbi.srWindow.Bottom);
            printf("    top: %d\n", csbi.srWindow.Top);
            printf("    columns: %d\n", columns);
            printf("    rows: %d\n", rows);
            printf("}\n");
            printf("\n");
        }
    }
    printf("hello world %c\n", ch);
    disableRawMode();
}
