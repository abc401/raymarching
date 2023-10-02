#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "vec.h"
#include "sdf.h"

#define INIT_WINDOW_SIZE 500
#define FPS 30

typedef struct App
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} App;

rational maprange(rational value, rational from_low, rational from_high, rational to_low, rational to_high)
{
    rational ilerp = (value - from_low) / (from_high - from_low);
    return to_low + ilerp * (to_high - to_low);
}

bool cast_ray(Vec3 ro, Vec3 rd)
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

rational screen_dist = 1.0;

void sdl_err()
{
    printf("SDL error: %s", SDL_GetError());
    exit(EXIT_FAILURE);
}

void draw_point(App app, size_t x, size_t y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if (SDL_SetRenderDrawColor(app.renderer, r, g, b, a) < 0)
    {
        sdl_err();
    }
    if (SDL_RenderDrawPoint(app.renderer, x, y) < 0)
    {
        sdl_err();
    }
}

void draw(App app)
{
    int width, height;
    SDL_GetWindowSize(app.window, &width, &height);
    Vec3 origin = Vec3_new(0, 0, 0);
    rational aspect_ratio = width / (rational)height;
    //     printf("aspect_ratio: %f, rows: %d, cols: %d\n", aspect_ratio, rows, cols);

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            Vec3 ro = Vec3_new(
                maprange(x, 0, width - 1, -1, 1),
                maprange(y, 0, height - 1, -aspect_ratio, aspect_ratio),
                // (col - (cols / 2.0)) / (cols / 2.0),
                // (row - (rows / 2.0)) / (rows / 2.0),
                screen_dist);
            Vec3 rd = Vec3_norm(ro);
            if (cast_ray(ro, rd))
            {
                draw_point(app, x, y, 255, 255, 255, 255);
            }
            else
            {
                draw_point(app, x, y, 0, 0, 0, 255);
            }
        }
    }
    SDL_RenderPresent(app.renderer);
}

int main(int argc, char **argv)
{
    App app;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        sdl_err();
    }
    app.window = SDL_CreateWindow("RayMarching", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INIT_WINDOW_SIZE, INIT_WINDOW_SIZE, SDL_WINDOW_RESIZABLE);
    if (app.window == NULL)
    {
        sdl_err();
    }
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (app.renderer == NULL)
    {
        sdl_err();
    }

    bool go = true;
    while (go)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                go = false;
            }
        }
        draw(app);
        SDL_Delay(1000 / FPS);
    }
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
