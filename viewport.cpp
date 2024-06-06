#include <SDL2/SDL.h>
#include <iostream>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MINIMAP_SIZE = 200;
bool minimapOn = true;

void start_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not start_sdlialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("SDL Minimap Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void end_sdl()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_shapes()
{
    // Render some elements to the main scene
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect rect = {100, 100, 200, 200};
    SDL_RenderFillRect(renderer, &rect);
}

void draw_mini_map()
{
    // Set the viewport for the minimap
    SDL_Rect minimapViewport = {SCREEN_WIDTH - MINIMAP_SIZE - 10, 10, MINIMAP_SIZE, MINIMAP_SIZE};
    SDL_RenderSetViewport(renderer, &minimapViewport);

    // Clear minimap background
    SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xFF); // Dark grey background for minimap
    SDL_RenderFillRect(renderer, nullptr);

    // Scale down the entire scene for the minimap
    float scaleX = MINIMAP_SIZE / static_cast<float>(SCREEN_WIDTH);
    float scaleY = MINIMAP_SIZE / static_cast<float>(SCREEN_HEIGHT);
    SDL_RenderSetScale(renderer, scaleX, scaleY);

    // Reset the scale and viewport
    SDL_RenderSetScale(renderer, 1.0, 1.0);
    SDL_RenderSetViewport(renderer, NULL);
}

void handle(bool quit)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_m:
                minimapOn = !minimapOn;
                break;
            case SDLK_UP:
                mouseY -= 5;
                break;
            case SDLK_DOWN:
                mouseY += 5;
                break;
            case SDLK_LEFT:
                mouseX -= 5;
                break;
            case SDLK_RIGHT:
                mouseX += 5;
                break;
            }
        }
    }
}

void update()
{
    // Add any game logic updates here
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    draw_shapes();

    if (minimapOn)
    {
        draw_mini_map();
    }

    SDL_RenderPresent(renderer);
}

void run_sdl()
{
    bool quit = false;
    while (!quit)
    {
        handle(quit);
        update();
        draw();
    }
}

int main(int argc, char *args[])
{
    start_sdl();
    run_sdl();
    end_sdl();
    return 0;
}
