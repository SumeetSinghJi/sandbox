#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <unordered_map>
#include <vector>
#ifdef __WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#endif
#include "headers/WebserverClient.hpp"

/**
 * TO DO
 *
 * POST/GET methods convert to JSON string so that you can POST using Boost or SDL_net
 * webserver save game state - use filesystem possibly to save state of scene vector
 * draw a fence and prevent payer from moving beyond it unless they jump
 * implement a camera
 * Implement a shoot function that works on direction
 * Create a seperate local webserver file and executable then test
 * Add to BubbleUP
 */

const int WORLD_WIDTH = 1600;  // double screen/camera size
const int WORLD_HEIGHT = 1200; // double screen/camera size
const int SCREEN_WIDTH = 800;  // double screen/camera size
const int SCREEN_HEIGHT = 600; // double screen/camera size

WebserverClient ws{};

SDL_Window *window{};
SDL_Renderer *renderer{};
SDL_Rect cameraRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Texture *backgroundTexture{};
SDL_Texture *houseTexture{};
SDL_Rect houseRect = {200, 200, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6};

class Player
{
private:
    int playerID{};
    SDL_Renderer *renderer{};
    SDL_Rect rect{};
    std::vector<std::string> walkingTextures{};
    int xVel{};
    int yVel{};
    int currentAnimationFrame{};
    std::chrono::steady_clock::time_point lastFrameChange{};
    int animationDelay = 200;
    std::string texturePath{};
    std::unordered_map<std::string, SDL_Texture *> textureMap{};
    SDL_Texture *texture{};
    std::string direction{};

public:
    Player(int playerID, int x, int y, int w, int h, std::vector<std::string> walkingTextures)
        : playerID(playerID), rect({x, y, w, h}), walkingTextures(walkingTextures)
    {
        std::cout << "Constructed: Player" << std::endl;
        lastFrameChange = std::chrono::steady_clock::now();
    }
    ~Player()
    {
        std::cout << "Deconstructed: Player" << std::endl;
        for (auto &texture : textureMap)
        {
            SDL_DestroyTexture(texture.second);
        }
    }
    int get_player_id() const
    {
        return playerID;
    }
    void set_renderer(SDL_Renderer *r)
    {
        renderer = r;
    }
    int get_x_position() const
    {
        return rect.x;
    }
    int get_y_position() const
    {
        return rect.y;
    }
    void set_position(int xPos, int yPos)
    {
        rect.x = xPos;
        rect.y = yPos;
    }
    void set_direction(const std::string &dir)
    {
        direction = dir;
    }
    std::string get_direction() const
    {
        return direction;
    }
    void set_texture_map()
    {
        for (const auto &filePath : walkingTextures)
        {
            if (textureMap.find(filePath) == textureMap.end())
            {
                // Texture not found, load it
                texture = IMG_LoadTexture(renderer, filePath.c_str());
                if (!texture)
                {
                    std::cerr << "Error: Failed to load texture: " << filePath << IMG_GetError() << std::endl;
                }
                else
                {
                    // Texture loaded successfully, store it in the map
                    textureMap[filePath] = texture;
                    // std::cout << "Success: Texture loaded: " << filePath << std::endl;
                }
            }
        }
    }

    void set_animation_texture()
    {
        if (!texturePath.empty())
        {
            // Try to find texture in the map
            auto it = textureMap.find(texturePath);
            if (it != textureMap.end())
            {
                // Texture found in the map, use it
                texture = it->second;
            }
            else
            {
                // Texture not found, load it
                texture = IMG_LoadTexture(renderer, texturePath.c_str());
                if (!texture)
                {
                    std::cerr << "Error: Failed to load texture: " << texturePath << IMG_GetError() << std::endl;
                }
                else
                {
                    // Texture loaded successfully, store it in the map
                    textureMap[texturePath] = texture;
                    std::cout << "Success: Texture loaded: " << texturePath << std::endl;
                }
            }
        }
    }

    void update_animation()
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameChange).count();

        if (elapsedTime >= animationDelay)
        {
            lastFrameChange = currentTime;
            currentAnimationFrame = (currentAnimationFrame + 1) % walkingTextures.size();

            texturePath = walkingTextures[currentAnimationFrame];
        }
    }
    void draw_player(int cameraX, int cameraY)
    {
        rect.x = cameraX;
        rect.y = cameraY;
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
};

std::vector<Player *> players{};

// WEBSERVER LOGIC
std::vector<Player *> serverPlayers{};
void webserver_save_game_state()
{
}
void webserver_load_game_state()
{
}
void webserver_process_player_handle(int playerID, int x, int y, const std::string &direction)
{
    // Find the player in the serverPlayers vector and update its position
    for (auto &p : serverPlayers)
    {
        if (p->get_player_id() == playerID)
        {
            p->set_position(p->get_x_position() + x, p->get_y_position() + y);
            p->set_direction(direction);
            std::cout << "Server updated player " << playerID << " position: x: " << p->get_x_position() << " y: " << p->get_y_position() << " Direction: " << p->get_direction() << std::endl;
            return;
        }
    }
}
void webserver_process_player_vector(std::vector<Player *> players)
{
    serverPlayers = players;
}

// CLIENT LOGIC
void initialise_players()
{
    int playerID = players.size() + 1; // Start with 1 if players vector is not empty
    Player *player = new Player(playerID, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, std::vector<std::string>{"assets/turtle.png", "assets/turtle.png"});
    players.push_back(player);
}
void initialise_players_textures()
{
    for (auto &p : players) // Iterate by reference
    {
        p->set_renderer(renderer);
        p->set_texture_map();
    }
}
void POST_player_vector_to_server(std::vector<Player *> players)
{
    // send JSON string
    webserver_process_player_vector(players);
}
void POST_movement_to_server(int playerID, int x, int y, const std::string &direction)
{
    // send JSON string
    webserver_process_player_handle(playerID, x, y, direction);
}
void GET_network_messages()
{
    // Update the local players vector with the data from the server
    players = serverPlayers;
}
SDL_Texture *load_texture(const std::string &textureFilePath)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, textureFilePath.c_str());
    if (!texture)
    {
        std::cerr << "Error: Failed to load texture: " << textureFilePath << ": " << IMG_GetError() << std::endl;
    }
    return texture;
}

void load_textures()
{
    backgroundTexture = load_texture("assets/farm-day.png");
    houseTexture = load_texture("assets/house-day.png");
}

void sdl_destroy(SDL_Window *window, SDL_Renderer *renderer)
{
    // Destroy renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDLNet_Quit();
    SDL_Quit();
}
void start_sdl(SDL_Window *&window, SDL_Renderer *&renderer)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create window
    window = SDL_CreateWindow("Fireworks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    if (SDLNet_Init() < 0)
    {
        std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}
void handle_inputs(bool &quit)
{
    // Event handler
    SDL_Event e;
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        if (e.type == SDL_KEYDOWN)
        {
            for (auto p : players)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    POST_movement_to_server(p->get_player_id(), 0, -5, "UP");
                    break;
                case SDLK_DOWN:
                    POST_movement_to_server(p->get_player_id(), 0, 5, "DOWN");
                    break;
                case SDLK_LEFT:
                    POST_movement_to_server(p->get_player_id(), -5, 0, "LEFT");
                    break;
                case SDLK_RIGHT:
                    POST_movement_to_server(p->get_player_id(), 5, 0, "RIGHT");
                    break;
                case SDLK_SPACE:
                    // Example: Jump up in z axis
                    POST_movement_to_server(p->get_player_id(), 0, 0, "JUMP");
                    break;
                default:
                    break;
                }
            }
        }
    }
}
void update_camera_follow_player()
{
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;

    for (auto *p : players)
    {
        int playerX = p->get_x_position();
        int playerY = p->get_y_position();

        if (playerX < minX)
            minX = playerX;
        if (playerY < minY)
            minY = playerY;
        if (playerX + SCREEN_WIDTH > maxX)
            maxX = playerX + SCREEN_WIDTH;
        if (playerY + SCREEN_HEIGHT > maxY)
            maxY = playerY + SCREEN_HEIGHT;
    }

    // Adjust camera position to keep all players in view
    cameraRect.x = minX - (SCREEN_WIDTH / 2);
    cameraRect.y = minY - (SCREEN_HEIGHT / 2);

    // Clamp camera position to world boundaries
    if (cameraRect.x < 0)
        cameraRect.x = 0;
    if (cameraRect.y < 0)
        cameraRect.y = 0;
    if (cameraRect.x + SCREEN_WIDTH > WORLD_WIDTH)
        cameraRect.x = WORLD_WIDTH - SCREEN_WIDTH;
    if (cameraRect.y + SCREEN_HEIGHT > WORLD_HEIGHT)
        cameraRect.y = WORLD_HEIGHT - SCREEN_HEIGHT;
}
void update_player_stay_within_world_bounds()
{
    for (auto *p : players)
    {
        if (p->get_x_position() < 0)
        {
            p->set_position(p->get_y_position(), 0);
        }
        if (p->get_y_position() < 0)
        {
            p->set_position(0, p->get_x_position());
        }
        if (p->get_x_position() + SCREEN_WIDTH > WORLD_WIDTH)
        {
            p->set_position(p->get_y_position(), WORLD_WIDTH - SCREEN_WIDTH);
        }
        if (p->get_y_position() + SCREEN_HEIGHT > WORLD_HEIGHT)
        {
            p->set_position(WORLD_HEIGHT - SCREEN_HEIGHT, p->get_x_position());
        }
    }
}
void update_collission_logic() {
}
void update()
{
    update_camera_follow_player();
    update_player_stay_within_world_bounds();
    GET_network_messages();
}
void draw_house()
{
    SDL_RenderCopy(renderer, houseTexture, nullptr, &houseRect);
}
void draw(SDL_Renderer *renderer)
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    draw_house();
    for (auto p : players)
    {
        p->draw_player(p->get_x_position() - cameraRect.x, p->get_y_position() - cameraRect.y);
    }
    

    // Render present
    SDL_RenderPresent(renderer);
}
void run_sdl(SDL_Window *&window, SDL_Renderer *&renderer)
{
    // Main loop flag
    bool quit = false;

    // Main loop
    while (!quit)
    {
        handle_inputs(quit);
        update();
        draw(renderer);
        SDL_Delay(60); /** Limit FPS */
    }
}
int main(int argc, char *argv[])
{
    // Seed random number generator
    srand(time(nullptr));

    // Initialize SDL
    start_sdl(window, renderer);
    load_textures();
    initialise_players();
    initialise_players_textures();
    POST_player_vector_to_server(players);
    run_sdl(window, renderer);
    sdl_destroy(window, renderer);

    return 0;
}