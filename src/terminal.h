
#ifndef TERMINAL_H
#define TERMINAL_H
#include <Windows.h>

HANDLE getStdHandle(DWORD nStdHandle);

CONSOLE_SCREEN_BUFFER_INFO get_csbi();

void setCursorPos(int row, int col);

void disableRawMode();

void enableRawMode();

#endif