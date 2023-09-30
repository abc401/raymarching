#include <stdio.h>
#include <stdbool.h>

#include "sdf.h"
#include "terminal.h"

void blit(char *buffer)
{
    setCursorPos(1, 1);
    CONSOLE_SCREEN_BUFFER_INFO csbi = get_csbi();
    size_t columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size_t rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    printf("%.*s", (columns * rows), buffer);
}

int main(int, char **)
{
    enableRawMode();

    char buf_ch = '0';
    while (true)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi = get_csbi();
        size_t columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size_t rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        char buffer[rows][columns];
        for (size_t row = 0; row < rows; row++)
        {
            for (size_t col = 0; col < columns; col++)
            {
                buffer[row][col] = buf_ch;
                buf_ch++;
                if (buf_ch > '9')
                {
                    buf_ch = '0';
                }
            }
        }
        blit(buffer);
        char ch = getchar();
        if (ch == 'q')
        {
            break;
        }
    }
    disableRawMode();
}
