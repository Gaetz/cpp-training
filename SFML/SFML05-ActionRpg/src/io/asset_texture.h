#ifndef ASSET_TEXTURE_H
#define ASSET_TEXTURE_H

#include <SFML/Graphics/Texture.hpp>
#include "../core/asset_manager.h"

class Asset_Texture : public AssetManager<Asset_Texture, sf::Texture>
{
public:
    Asset_Texture() : AssetManager("assets/data/config/textures.cfg") {}

    sf::Texture* load(const std::string);
};
#endif // ASSET_TEXTURE_H
