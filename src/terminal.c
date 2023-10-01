#include <stdio.h>
#include "terminal.h"

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

CONSOLE_SCREEN_BUFFER_INFO get_csbi()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(getStdHandle(STD_OUTPUT_HANDLE), &csbi) == 0)
    {
        fprintf(stderr, "[Error] GetConsoleScreenBufferInfo: %d", GetLastError);
        exit(EXIT_FAILURE);
    }
    return csbi;
}

void setCursorPos(int row, int col)
{
    printf("\033[%d;%dH", row, col);
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
    printf("\033[?25l");
}