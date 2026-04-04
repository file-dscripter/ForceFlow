#include <iostream>
#include <cmath>
#include <vector>

#include <SDL3/SDL.h>

#include "constants.h"

struct square {
    float squareXPos; 
    float squareYPos; 
    float squareMass; 
    float squareVelocity;
};

struct square sq;

SDL_Window* createWindow(void);
SDL_Renderer* createRenderer(SDL_Window* window);

void renderBackground(SDL_Renderer* renderer);
void renderSquare(SDL_Renderer* renderer, float enteredHeight);

int main(void) 
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = createWindow();
    SDL_Renderer* renderer = createRenderer(win);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        renderBackground(renderer);

        renderSquare(renderer, 50.0f);

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

void renderSquare(SDL_Renderer* renderer, float enteredHeight) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_FRect s;
    s.x = (WIDTH/2) - 50; 
    sq.squareXPos = s.x;

    s.y = (HEIGHT/2)-enteredHeight;
    sq.squareYPos = s.y;

    s.w = SQUARE_WIDTH;
    s.h = SQUARE_HEIGHT;

    SDL_RenderFillRect(renderer, &s);
}