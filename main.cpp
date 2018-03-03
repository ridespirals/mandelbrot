#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    bool quit = false;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        return 1;
    } else {
        window = SDL_CreateWindow(
            "An SDL2 Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            // SDL_WINDOW_SHOWN
            SDL_WINDOW_OPENGL
        );
        if (window == NULL) {
            printf("Could not create window %s\n", SDL_GetError());
            return 1;
        } else {
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                surface = SDL_GetWindowSurface(window);

                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xf2, 0x55, 0x55));
                SDL_UpdateWindowSurface(window);

            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
