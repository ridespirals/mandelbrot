#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

std::string programName = "ride_spirals - OpenGL Test";

SDL_Window* mainWindow;
SDL_GLContext mainContext;

bool SetOpenGLAttributes();
void CheckSDLError(int line);

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to init SDL" << std::endl;
        return -1;
    }

    mainWindow = SDL_CreateWindow(programName.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            512, 512, SDL_WINDOW_OPENGL);

    if (!mainWindow) {
        std::cout << "Failed to create window" << std::endl;
        CheckSDLError(__LINE__);
        return -1;
    }

    mainContext = SDL_GL_CreateContext(mainWindow);

    SetOpenGLAttributes();

    SDL_GL_SetSwapInterval(1);

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);

    // main loop
    bool loop = true;
    while (loop) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                loop = false;
            
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_r:
                        glClearColor(1.0, 0.0, 0.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        SDL_GL_SwapWindow(mainWindow);
                        break;
                    case SDLK_g:
                        glClearColor(0.0, 1.0, 0.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        SDL_GL_SwapWindow(mainWindow);
                        break;
                    case SDLK_b:
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        SDL_GL_SwapWindow(mainWindow);
                        break;
                    default: break;
                }
            }
        }
    }

    // cleanup
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}

bool SetOpenGLAttributes() {
    // set opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards should be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // turn on double buffering with a 24bit Z buffer
    // may need to change to 16 or 32
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
}

void CheckSDLError(int line = -1) {
    std::string error = SDL_GetError();
    if (error != "") {
        std::cout << "SDL Error: " << error << std::endl;
        if (line != -1) {
            std::cout << "\tLine: " << line << std::endl;
        }
        SDL_ClearError();
    }
}
