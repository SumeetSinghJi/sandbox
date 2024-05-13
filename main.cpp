
SDL_Texture *snailTexture{};
SDL_Rect houseRect = {(SCREEN_WIDTH - 300) / 2, (SCREEN_HEIGHT - 300) / 2, 300, 300}; // house is in middle of screen


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
    snailTexture = load_texture("assets/snail.png");
}
