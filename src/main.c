#include <stdio.h>
#include <stdbool.h>

#include "vec.h"
#include "terminal.h"
#include "sdf.h"

void blit(char *buffer)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi = get_csbi();
    size_t columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size_t rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    for (size_t row = 0; row < rows; row++)
    {
        setCursorPos(row + 1, 1);

        printf("%.*s", columns, &buffer[row * columns]);
    }
}

bool cast_ray(char *pixel, Vec3 ro, Vec3 rd)
{
    Circle c = {
        .center = Vec3_new(0.0, 0.0, 70),
        .radius = 50,
    };

    rational delta = 0.5;
    rational sdf;
    while (true)
    {
        sdf = Circle_sdf(c, ro);
        ro = Vec3_add(ro, Vec3_mul(rd, sdf * delta));

        if (sdf < MIN_SDF || sdf > MAX_SDF)
        {
            break;
        }
    }
    return sdf < MIN_SDF;
}

void draw(char *surface, size_t rows, size_t cols)
{
    Vec3 origin = Vec3_new(0, 0, 0);
    rational screen_dist = 1.0;

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < cols; col++)
        {
            Vec3 ro = Vec3_new(
                (col - (cols / 2.0)) / (cols / 2.0),
                (row - (rows / 2.0)) / (rows / 2.0),
                screen_dist);
            Vec3 rd = Vec3_norm(ro);
            if (cast_ray(surface + (row * cols + col), ro, rd))
            {
                surface[row * cols + col] = '#';
            }
            else
            {
                surface[row * cols + col] = ' ';
            }
        }
    }
}

int main(int, char **)
{
    // TODO: make it so that resizing the terminal window to a smaller size does not make the window scroll
    enableRawMode();

    while (true)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi = get_csbi();
        size_t columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size_t rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        char buffer[rows * columns];
        draw(buffer, rows, columns);
        blit(buffer);

        char ch = getchar();
        if (ch == 'q')
        {
            break;
        }
    }
    disableRawMode();
}
