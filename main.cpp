#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int W = 800;
const int H = 800;
/* long double min = -2.0; */
/* long double max = 2.0; */
long double min = -2.84;
long double max = 1.0;
long double factor = 1;

int ITERATIONS = 200;

/* float map(float val, float in_min, float in_max, float out_min, float out_max) { */
/*     return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; */
/* } */
long double map(long double val, long double in_min, long double in_max, long double out_min, long double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Renderer* renderer = NULL;
    bool quit = false;
    int count = 0;
    SDL_Event e;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
            &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }
    SDL_RenderSetLogicalSize(renderer, W, H);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }

        // zoom
        max -= 0.1 * factor;
        min += 0.15 * factor;
        factor *= 0.9349;
        ITERATIONS += 5;

        if (count > 30) {
            // bump iterations for better accuracy as we zoom in
            ITERATIONS += 5;
        }

        SDL_SetRenderDrawColor(renderer, 0x37, 0x2f, 0xbe, 0xff);
        SDL_RenderClear(renderer);

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {

                long double a = map(x, 0, W, min, max);
                long double b = map(y, 0, H, min, max);

                long double ai = a;
                long double bi = b;

                int n = 0;
                for (int i = 0; i < ITERATIONS; i++) {
                    long double a1 = a*a - b*b;
                    long double b1 = 2 * a * b;

                    a = a1 + ai;
                    b = b1 + bi;

                    if ((a + b) > 2.0) {
                        break;
                    }

                    n++;
                }

                int bright = map(n, 0, ITERATIONS, 0, 255);

                if (n == ITERATIONS || bright < 20) {
                    bright = 0;
                }

                int red = map(bright * bright, 0, 6502, 0, 255);
                int green = bright;
                int blue = map(sqrt(bright), 0, sqrt(255), 0, 255);

                SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
