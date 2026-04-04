#include <iostream>
#include <cmath>
#include <vector>

#include <SDL3/SDL.h>

#include "constants.h"

struct square {
    float squareXPos; 
    float squareYPos; 
    float squareMass; 
    float forceApplied;
};

struct square sq;

SDL_Window* createWindow(void);
SDL_Renderer* createRenderer(SDL_Window* window);

void renderBackground(SDL_Renderer* renderer);
void renderSurface(SDL_Renderer* renderer);
void renderSquare(SDL_Renderer* renderer);

int main(void) 
{


    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = createWindow();
    SDL_Renderer* renderer = createRenderer(win);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // float deltaTime = 1.0f / 60.0f;

        renderBackground(renderer);

        renderSurface(renderer);

        renderSquare(renderer);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }
    }

    return EXIT_SUCCESS;
}

SDL_Window* createWindow(void) {
    SDL_Window* win = SDL_CreateWindow(TITLE, WIDTH, HEIGHT, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL);
    return win;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    return renderer;
}

void renderBackground(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 175, 175, 175, 255);
    SDL_RenderClear(renderer);
}

void renderSurface(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
    SDL_FRect surface;
    surface.x = 0;
    surface.y = SURFACE_YPOS;

    surface.w = SURFACE_WIDTH;
    surface.h = SURFACE_HEIGHT;

    SDL_RenderFillRect(renderer, &surface);
}

void renderSquare(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_FRect block;
    block.x = SQUARE_XPOS; 
    sq.squareXPos = block.x;

    block.y = (SURFACE_YPOS - SQUARE_HEIGHT);
    sq.squareYPos = block.y;

    block.w = SQUARE_WIDTH;
    block.h = SQUARE_HEIGHT;

    SDL_RenderFillRect(renderer, &block);
}