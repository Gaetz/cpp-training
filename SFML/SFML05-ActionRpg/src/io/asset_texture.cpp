#include "asset_texture.h"

sf::Texture* Asset_Texture::load(const std::string path)
{
    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile(Utils::getWorkingDirectory() + path)) {
        delete texture;
        texture = nullptr;
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
    return texture;
}
