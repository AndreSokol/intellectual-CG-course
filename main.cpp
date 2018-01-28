#include "SDL.h"
#include <random>

uint8_t calcVignette(int i, int j) {
    double dist = sqrt((i - 300) * (i - 300) + (j - 300) * (j - 300));
    uint8_t ans = 255 - dist / 600 * 255;
    return ans;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, 600, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 600; ++i) {
        for (int j = 0; j < 600; j++) {
            uint8_t colorValue = calcVignette(i, j);
            SDL_SetRenderDrawColor(renderer, colorValue, colorValue, colorValue, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}