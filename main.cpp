#include <iostream>
#include <cmath>

#include <SDL3/SDL.h>

#include "constants.h"

struct square {
    float squareXPos; 
    float squareYPos; 
    float squareMass; 
    float forceApplied;
    float squareVelocity;
};

struct square sq;

SDL_Window* createWindow(void);
SDL_Renderer* createRenderer(SDL_Window* window);

void renderBackground(SDL_Renderer* renderer);
void renderSurface(SDL_Renderer* renderer);
void renderSquare(SDL_Renderer* renderer, float xPosition);

double calculateAcceleration(float forceApplied, double mu, float squareMass, float squareVelocity, float gravitationalForce);

int main(void) 
{
    // square mass
    std::cout << "Enter mass (Kg): ";
    std::cin >> sq.squareMass;
    while (sq.squareMass < 0) {
        std::cout << "Enter mass (Kg): ";
        std::cin >> sq.squareMass;
    }

    // force applied to square
    std::cout << "Enter force applied to block (N): ";
    std::cin >> sq.forceApplied;

    // mu value
    double mu;
    std::cout << "Enter mu value (0-1): ";
    std::cin >> mu;
    while (mu < 0 || mu > 1) {
        std::cout << "Enter mu value (0-1): ";
        std::cin >> mu;
    }

    sq.squareVelocity = 0.0f;
    sq.squareXPos = SQUARE_XPOS;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = createWindow();
    SDL_Renderer* renderer = createRenderer(win);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        float deltaTime = 1.0f / 60.0f;
        double acceleration;

        if (sq.squareVelocity > 0) {
            sq.forceApplied = 0;
        }

        double maxFriction = mu * (sq.squareMass * GRAVITATIONAL_FORCE);
        if (fabs(sq.forceApplied) <= maxFriction && sq.squareVelocity == 0) {
            acceleration = 0;
        } else {
            acceleration = calculateAcceleration(sq.forceApplied, mu, sq.squareMass, sq.squareVelocity, GRAVITATIONAL_FORCE);
        }

        if (sq.squareVelocity > 0 && acceleration < 0) {
            if (sq.squareVelocity + acceleration * deltaTime < 0) {
                sq.squareVelocity = 0;
                acceleration = 0;
            }
        }

        sq.squareVelocity += acceleration * deltaTime;
        sq.squareXPos += sq.squareVelocity * deltaTime;

        renderBackground(renderer);

        renderSurface(renderer);

        renderSquare(renderer, sq.squareXPos);

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

void renderSquare(SDL_Renderer* renderer, float xPosition) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_FRect block;
    block.x = xPosition * PIXELS_PER_METER;

    block.y = (SURFACE_YPOS - SQUARE_HEIGHT);
    sq.squareYPos = block.y;

    block.w = SQUARE_WIDTH;
    block.h = SQUARE_HEIGHT;

    SDL_RenderFillRect(renderer, &block);
}

double calculateAcceleration(float forceApplied, double mu, float squareMass, float squareVelocity, float gravitationalForce) {
    double friction = mu * squareMass * gravitationalForce;

    if (squareVelocity > 0) {
        friction = -friction;
    } else if (squareVelocity < 0) {
        friction = friction;
    } else {
        friction = (forceApplied > 0) ? -friction : friction;
    }

    double netForce = forceApplied + friction;
    double acceleration = netForce / squareMass;

    return acceleration;
}
