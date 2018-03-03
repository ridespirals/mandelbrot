#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int W = 800;
const int H = 800;

float min, max, factor;
int ITERATIONS;

float start_min = -2.87;
float start_max = 1.0;
float start_factor = 1;
int start_iterations = 200;
void reset() {
    min = start_min;
    max = start_max;
    factor = start_factor;
    ITERATIONS = start_iterations;
}

float map(float val, float in_min, float in_max, float out_min, float out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Renderer* renderer = NULL;
    bool quit = false;
    int count = 0;
    SDL_Event e;

    reset();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI,
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

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_Q]) {
            quit = true;
            break;
        }
        if (state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_DELETE]) {
            reset();
            count = 0;
        }
        if (state[SDL_SCANCODE_SPACE]) {
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

            for (int x = 0; x < W; x++) {
                for (int y = 0; y < H; y++) {

                    float cr = map(x, 0, W, min, max);
                    float ci = map(y, 0, H, min, max);

                    float zr = 0.0;
                    float zi = 0.0;
                    float zrsq = zr * zr;
                    float zisq = zi * zi;

                    int n = 0;
                    while (n < ITERATIONS && zrsq + zisq <= 4.0) {
                        zi = (zr + zi) * (zr + zi) - zrsq - zisq;
                        zi += ci;
                        zr = zrsq - zisq + cr;

                        zrsq = zr * zr;
                        zisq = zi * zi;
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
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
