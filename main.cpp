#include <iostream>
#include <cmath>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

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

double calculateAcceleration(float forceApplied, float squareMass, float squareVelocity, float frictionMax);
float calculateDisplacement(float xPosition);
double calculateFrictionMax(double mu, float squareMass, float gravitationalForce);

void renderAccelerationText(SDL_Renderer* renderer, double acceleration);
void renderVelocityText(SDL_Renderer* renderer, float velocity);
void renderDisplacementText(SDL_Renderer* renderer, float displacement);

int main(void) 
{
    // square mass
    std::cout << "Enter mass (Kg): ";
    std::cin >> sq.squareMass;
    while (sq.squareMass < 0) {
        std::cout << "Enter mass (Kg): ";
        std::cin >> sq.squareMass;
    }

    // mu value
    double mu;
    std::cout << "Enter mu value (0-1): ";
    std::cin >> mu;
    while (mu < 0 || mu > 1) {
        std::cout << "Enter mu value (0-1): ";
        std::cin >> mu;
    }

    float frictionMax = calculateFrictionMax(mu, sq.squareMass, GRAVITATIONAL_FORCE);
    std::cout << "Friction Max: " << frictionMax;
    std::cout << " Newtons" << std::endl;

    // force applied to square
    std::cout << "Enter force applied to block (N): ";
    std::cin >> sq.forceApplied;

    bool forceHasBeenApplied = false;

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

        if (!forceHasBeenApplied) {
            if (fabs(sq.forceApplied) > frictionMax) {
                sq.squareVelocity = sq.forceApplied / sq.squareMass;
            } else {
                sq.squareVelocity = 0;
            }
            forceHasBeenApplied = true;
        }

        acceleration = calculateAcceleration(0, sq.squareMass, sq.squareVelocity, frictionMax);

        if (sq.squareVelocity > 0 && acceleration < 0) {
            if (sq.squareVelocity + acceleration * deltaTime < 0) {
                sq.squareVelocity = 0;
                acceleration = 0;
            }
        }

        sq.squareVelocity += acceleration * deltaTime;
        sq.squareXPos += sq.squareVelocity * deltaTime;

        float currentDisplacement = calculateDisplacement(sq.squareXPos);

        renderBackground(renderer);

        renderSurface(renderer);

        renderSquare(renderer, sq.squareXPos);

        renderAccelerationText(renderer, acceleration);
        renderVelocityText(renderer, sq.squareVelocity);
        renderDisplacementText(renderer, currentDisplacement);

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

double calculateAcceleration(float forceApplied, float squareMass, float squareVelocity, float frictionMax) {
    if (squareVelocity > 0) {
        frictionMax = -frictionMax;
    } else if (squareVelocity < 0) {
        frictionMax = frictionMax;
    } else {
        frictionMax = 0;
    }

    double netForce = forceApplied + frictionMax;
    double acceleration = netForce / squareMass;

    return acceleration;
}

float calculateDisplacement(float xPosition) {
    float displacement = xPosition - SQUARE_XPOS;
    return displacement;
}

double calculateFrictionMax(double mu, float squareMass, float gravitationalForce) {
    double frictionMax = mu * squareMass * gravitationalForce;
    return frictionMax;
}

void renderAccelerationText(SDL_Renderer* renderer, double acceleration) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderDebugTextFormat(renderer, 1.0f, 1.0f, "Acceleration: %.2f m/s^2", acceleration);
}

void renderVelocityText(SDL_Renderer* renderer, float velocity) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderDebugTextFormat(renderer, 1.0f, 10.0f, "Velocity: %.2f m/s", velocity);
}

void renderDisplacementText(SDL_Renderer* renderer, float displacement) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderDebugTextFormat(renderer, 1.0f, 20.0f, "Displacement: %.2f m", displacement);
}

