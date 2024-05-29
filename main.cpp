#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <unordered_map>
#include <random>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#ifdef _WIN32
#include <winsock2.h>
#include <boost/asio.hpp> // for online services
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif
#include <filesystem>

// FORWARD DECLARATIONS
class Entity
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
    Entity(int playerID, int x, int y, int w, int h, std::vector<std::string> walkingTextures)
        : playerID(playerID), rect({x, y, w, h}), walkingTextures(walkingTextures)
    {
        std::cout << "Constructed: Entity" << std::endl;
        lastFrameChange = std::chrono::steady_clock::now();
    }
    virtual ~Entity()
    {
        std::cout << "Deconstructed: Entity" << std::endl;
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
        rect.x += xPos;
        rect.y += yPos;
    }
    SDL_Rect get_rect() const
    {
        return rect;
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
    void draw_entity(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    void update_collission_logic(std::vector<Entity *> &entities)
    {
        for (Entity *e : entities)
        {
            SDL_Rect thisRect = this->get_rect();
            SDL_Rect collidedEntity = e->get_rect();

            if (e == this)
            {
                continue;
            }

            if (SDL_HasIntersection(&thisRect, &collidedEntity))
            {
                std::cout << this->get_player_id() << " collided with: " << e->get_player_id() << std::endl;

                int dx = thisRect.x + thisRect.w / 2 - collidedEntity.x - collidedEntity.w / 2;
                int dy = thisRect.y + thisRect.h / 2 - collidedEntity.y - collidedEntity.h / 2;

                int penetrationX = (thisRect.w + collidedEntity.w) / 2 - std::abs(dx);
                int penetrationY = (thisRect.h + collidedEntity.h) / 2 - std::abs(dy);

                if (penetrationX < penetrationY)
                {
                    if (dx < 0)
                    {
                        thisRect.x -= penetrationX / 2;
                        collidedEntity.x += penetrationX / 2;
                    }
                    else
                    {
                        thisRect.x += penetrationX / 2;
                        collidedEntity.x -= penetrationX / 2;
                    }
                }
                else
                {
                    if (dy < 0)
                    {
                        thisRect.y -= penetrationY / 2;
                        collidedEntity.y += penetrationY / 2;
                    }
                    else
                    {
                        thisRect.y += penetrationY / 2;
                        collidedEntity.y -= penetrationY / 2;
                    }
                }

                this->rect = thisRect;
                e->rect = collidedEntity;
            }
        }
    }
    void update_collision_world_bounds()
    {
        if (rect.x < 0)
        {
            rect.x = 0;
        }
        if (rect.y < 0)
        {
            rect.y = 0;
        }
        if (rect.x + rect.w > WORLD_WIDTH)
        {
            rect.x = WORLD_WIDTH - rect.w;
        }
        if (rect.y + rect.h > WORLD_HEIGHT)
        {
            rect.y = WORLD_HEIGHT - rect.h;
        }
    }
    void update_camera_displacement(SDL_Rect &cameraRect)
    {
        rect.x -= cameraRect.x;
        rect.y -= cameraRect.y;
    }
};
class Player : public Entity
{
public:
    Player(int playerID, int x, int y, int w, int h, std::vector<std::string> walkingTextures) 
        : Entity(playerID, x, y, w, h, walkingTextures) {}

    SDL_Point get_camera_displacement()
    {
        SDL_Point cameraDisplacement;
        cameraDisplacement.x = (this->get_rect().x + (this->get_rect().w / 2)) - (SCREEN_WIDTH / 2);
        cameraDisplacement.y = (this->get_rect().y + (this->get_rect().h / 2)) - (SCREEN_HEIGHT / 2);
        return cameraDisplacement;
    }

    void update_camera_follow_player()
    {
        if (clientPlayerID == get_player_id())
        {
            SDL_Point displacement = get_camera_displacement();
            cameraRect.x += displacement.x * 0.1;
            cameraRect.y += displacement.y * 0.1;
        }
    }
};
class Item : public Entity
{
private:
public:
    Item(int playerID, int x, int y, int w, int h, std::vector<std::string> walkingTextures) : Entity(playerID, x, y, w, h, walkingTextures) {}
};
class Enemy : public Entity
{
private:
public:
    Enemy(int playerID, int x, int y, int w, int h, std::vector<std::string> walkingTextures) : Entity(playerID, x, y, w, h, walkingTextures) {}
};
class Obstacle : public Entity
{
private:
public:
    Obstacle(int playerID, int x, int y, int w, int h, std::vector<std::string> walkingTextures) : Entity(playerID, x, y, w, h, walkingTextures) {}
};
std::vector<Entity *> entities{};

class WebserverHost
{
private:
    std::vector<Entity *> serverentities{};

public:
    WebserverHost() { std::cout << "Constructed: WebserverHost" << std::endl; }
    ~WebserverHost() { std::cout << "Deconstructed: WebserverHost" << std::endl; }
    void webserver_save_game_state()
    {
        // use filesystem to save serverentities to file
    }
    void webserver_load_game_state()
    {
        // use filesystem to load from file to serverentities
    }
    void webserver_process_player_handle(int playerID, int x, int y, const std::string &direction)
    {
        // Find the player in the serverentities vector and update its position
        for (auto &p : serverentities)
        {
            if (p->get_player_id() == playerID)
            {
                p->set_position(p->get_rect().x + x, p->get_rect().y + y);
                p->set_direction(direction);
                std::cout << "Server updated player " << playerID << " position: x: " << p->get_rect().x << " y: " << p->get_rect().y << " Direction: " << p->get_direction() << std::endl;
                return;
            }
        }
    }
    void webserver_process_player_vector(std::vector<Entity *> entities)
    {
        serverentities = entities;
    }
    std::vector<Entity *> get_entities() const
    {
        return serverentities;
    }
};

WebserverHost host{};

class WebserverClient
{
private:
    bool successResponse{};      /**< Response from webserver */
    std::string queryURL{};      /**< the url to query e.g. www.example.com */
    std::string queryProtocol{}; /**< the protocol to follow url query e.g. http*/
    // boost::asio::io_context io_context{};                /**< provides a context for I/O services e.g. sockets, timers, asynchronous functions */
    // boost::asio::ip::tcp::resolver resolver{io_context}; /**< resolve string address to endpoints. Same as a DNS/Domain name server */
    // boost::asio::ip::tcp::socket socket{io_context};     /**< socket for server being queried. Resolver passes the webaddress to use */
public:
    WebserverClient()
    {
        std::cout << "Constructed: WebserverClient" << std::endl;
    }
    ~WebserverClient()
    {
        std::cout << "Deconstructed: WebserverClient" << std::endl;
    }
    bool response_success() const
    {
        return successResponse;
    }
    void POST_player_vector_to_server(std::vector<Entity *> entities)
    {
        // POST JSON string
        host.webserver_process_player_vector(entities);
    }
    void POST_movement_to_server(int playerID, int x, int y, const std::string &direction)
    {
        // POST JSON string
        host.webserver_process_player_handle(playerID, x, y, direction);
    }
    void GET_network_messages()
    {
        // GET JSON string
        entities = host.get_entities();
    }
};

WebserverClient client{};

const int WORLD_WIDTH = 2000;  // double screen/camera size
const int WORLD_HEIGHT = 2000; // double screen/camera size
const int SCREEN_WIDTH = 800;  // double screen/camera size
const int SCREEN_HEIGHT = 600; // double screen/camera size
int clientPlayerID{};
int botPlayerID{};
SDL_Window *window{};
SDL_Renderer *renderer{};
TTF_Font *font{};
SDL_Rect cameraRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Texture *backgroundTexture{};
SDL_Texture *houseExteriorDayTexture{};
SDL_Texture *houseExteriorNightTexture{};
SDL_Texture *houseInteriorDayTexture{};
SDL_Texture *houseInteriorNightTexture{};
SDL_Rect houseRect = {200, 200, 200, 200};
SDL_Rect houseDoorRect = {100, 100, 50, 50};
bool isMultiplayerGame{};
int scene = 2;
int isNight{};

std::mt19937 gen(std::random_device{}());                    // for bot simulation
std::uniform_int_distribution<> dis(0, 3);                   // for bot simulation
std::chrono::steady_clock::time_point lastBotMovementTime{}; // for bot simulation

// CLIENT LOGIC
void initialise_players(int playerCount)
{
    for (int i{}; i < playerCount; ++i)
    {
        int playerID = entities.size() + 1; // Start with 1 if entities vector is not empty
        Player *player = new Player(playerID, SCREEN_WIDTH / 2 + playerID, SCREEN_HEIGHT / 2 + playerID, 100, 100, std::vector<std::string>{"assets/turtle.png", "assets/turtle.png"});
        entities.push_back(player);
    }
}
void initialise_players_textures()
{
    for (auto &p : entities) // Iterate by reference
    {
        p->set_renderer(renderer);
        p->set_texture_map();
    }
}
bool update_should_bot_move()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastBotMovementTime).count();
    return elapsedTime >= 2000; // Adjust this value to change the delay (in milliseconds)
}
void update_bot_movement_simulation_POST()
{
    int random_choice = dis(gen);
    for (Entity *e : entities)
    {
        if (e->get_player_id() == botPlayerID)
        {
            if (isMultiplayerGame)
            {
                switch (random_choice)
                {
                case 0:
                    client.POST_movement_to_server(2, 0, -5, "UP");
                    break;
                case 1:
                    client.POST_movement_to_server(2, 0, 5, "DOWN");
                    break;
                case 2:
                    client.POST_movement_to_server(2, -5, 0, "LEFT");
                    break;
                case 3:
                    client.POST_movement_to_server(2, 5, 0, "RIGHT");
                    break;
                default:
                    std::cerr << "Error: Invalid random choice" << std::endl;
                    break;
                }
            }
            else
            {
                switch (random_choice)
                {
                case 0:
                    e->set_position(0, -5);
                    break;
                case 1:
                    e->set_position(0, 5);
                    break;
                case 2:
                    e->set_position(-5, 0);
                    break;
                case 3:
                    e->set_position(5, 0);
                    break;
                default:
                    std::cerr << "Error: Invalid random choice" << std::endl;
                    break;
                }
            }
        }
    }
}

TTF_Font *load_font(const std::string &fontFilePath, const int &fontSize)
{
    TTF_Font *font = TTF_OpenFont(fontFilePath.c_str(), fontSize);
    if (!font)
    {
        std::cerr << "Error: Failed to load font: " << font << ": " << TTF_GetError() << std::endl;
    }
    return font;
}
void render_text(const std::string &text, int x, int y, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText, TTF_Font *font)
{
    SDL_Color textColor = {redText, greenText, blueText, alphaText};
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), textColor);

    if (textSurface)
    {
        int textWidth, textHeight;
        // Calculate textWidth and textHeight using TTF_SizeText
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        if (textTexture)
        {
            SDL_Rect textRect = {x, y, textWidth, textHeight};
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        }
        SDL_DestroyTexture(textTexture);
    }
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
    houseExteriorDayTexture = load_texture("assets/house-day.png");
    houseExteriorNightTexture = load_texture("assets/house-night.png");
    houseInteriorDayTexture = load_texture("assets/house-day.png");
    houseInteriorNightTexture = load_texture("assets/house-night.png");
}
void load_fonts()
{
    font = load_font("assets/fonts/noto-sans/NotoSans-Regular.ttf", 24);
}

void update_collisions_new_zone()
{
    for (Entity *e : entities)
    {
        if (Player *player = dynamic_cast<Player *>(e))
        {
            if (clientPlayerID == player->get_player_id())
            {
                // Go inside house
                if (player->get_rect().x == houseDoorRect.x || player->get_rect().y == houseDoorRect.y)
                {
                    scene = 3;
                }
                // go outside house
                if (player->get_rect().x == houseDoorRect.x || player->get_rect().y == houseDoorRect.y)
                {
                    scene = 2;
                }
            }
        }
    }
}

void draw_house_exterior()
{
    if (!isNight)
    {
        SDL_RenderCopy(renderer, houseExteriorDayTexture, nullptr, &houseRect);
    }
    else
    {
        SDL_RenderCopy(renderer, houseExteriorNightTexture, nullptr, &houseRect);
    }
}
void draw_house_interior()
{
    if (!isNight)
    {
        SDL_RenderCopy(renderer, houseInteriorDayTexture, nullptr, &houseRect);
    }
    else
    {
        SDL_RenderCopy(renderer, houseInteriorNightTexture, nullptr, &houseRect);
    }
}

void handle(bool &quit)
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
            for (auto p : entities)
            {
                if (clientPlayerID == p->get_player_id())
                {
                    if (isMultiplayerGame)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            client.POST_movement_to_server(p->get_player_id(), 0, -5, "UP");
                            break;
                        case SDLK_DOWN:
                            client.POST_movement_to_server(p->get_player_id(), 0, 5, "DOWN");
                            break;
                        case SDLK_LEFT:
                            client.POST_movement_to_server(p->get_player_id(), -5, 0, "LEFT");
                            break;
                        case SDLK_RIGHT:
                            client.POST_movement_to_server(p->get_player_id(), 5, 0, "RIGHT");
                            break;
                        case SDLK_SPACE:
                            client.POST_movement_to_server(p->get_player_id(), 0, 0, "JUMP");
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            p->set_position(0, -5);
                            break;
                        case SDLK_DOWN:
                            p->set_position(0, 5);
                            break;
                        case SDLK_LEFT:
                            p->set_position(-5, 0);
                            break;
                        case SDLK_RIGHT:
                            p->set_position(5, 0);
                            break;
                        case SDLK_SPACE:
                            p->set_position(0, 0);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
}
void update()
{
    if (isMultiplayerGame)
    {
        if (update_should_bot_move())
        {
            update_bot_movement_simulation_POST();
            lastBotMovementTime = std::chrono::steady_clock::now();
        }
        client.GET_network_messages();
    }

    // First, update all entity positions and check collisions
    for (Entity *e : entities)
    {
        e->update_collission_logic(entities);
        e->update_collision_world_bounds();
    }

    // Then, update camera positions based on the player
    for (Entity *e : entities)
    {
        if (Player *player = dynamic_cast<Player *>(e))
        {
            if (clientPlayerID == player->get_player_id())
            {
                player->update_camera_follow_player();
            }
        }
    }

    // Finally, update the camera displacement for all entities
    for (Entity *e : entities)
    {
        e->update_camera_displacement(cameraRect);
    }
}

void draw(SDL_Renderer *renderer)
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    render_text("Turtle Story कूर्म कथा", (SCREEN_WIDTH * 0.15), (SCREEN_HEIGHT * 0.1), 255, 255, 255, 255, font);

    for (auto e : entities)
    {
        e->draw_entity(renderer);
    }
    if (scene == 2)
    {
        draw_house_exterior();
    }
    if (scene == 3)
    {
        draw_house_interior();
    }

    SDL_RenderPresent(renderer);
}

void start_sdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error: Failes to initialise SDL" << SDL_GetError() << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Success: initialised: SDL2" << std::endl;
    }

    if (TTF_Init() != 0)
    {
        std::cerr << "Error: Failed to initialize SDL Font: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        std::cout << "Success: initialised: SDL2 TTF" << std::endl;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Error: Failed to initialize SDL IMG: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        std::cout << "Success: initialised: SDL2 Image" << std::endl;
    }

    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        std::cerr << "Error: Failed to initialize Audio: " << Mix_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        std::cout << "Success: initialised: SDL2 Mixer" << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cerr << "Error: Failed to open audio channel: " << Mix_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        std::cout << "Success: initialised: SDL2 Mixer Audio" << std::endl;
    }

    // Create window
    window = SDL_CreateWindow("Turtle Story कूर्म कथा", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
}
void run_sdl()
{
    // Main loop flag
    bool quit = false;

    // Main loop
    while (!quit)
    {
        handle(quit);
        update();
        draw(renderer);
        SDL_Delay(60); /** Limit FPS */
    }
}
void sdl_exit()
{
    // Destroy renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    // Seed random number generator
    srand(time(nullptr));

    std::cout << "STARTING SDL" << std::endl;

    start_sdl();

    load_textures();
    load_fonts();
    isMultiplayerGame = true;
    if (isMultiplayerGame)
    {
        initialise_players(2); // create 2 players, bot is second
        clientPlayerID = 1;
        botPlayerID = 2;
    }
    else
    {
        initialise_players(1);
        clientPlayerID = 1;
    }
    initialise_players_textures();
    client.POST_player_vector_to_server(entities);
    run_sdl();
    sdl_exit();

    return 0;
}