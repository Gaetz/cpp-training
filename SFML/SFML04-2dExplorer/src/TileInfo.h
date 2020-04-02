#ifndef TILEINFO_H
#define TILEINFO_H

#include <string>
#include "SharedContext.h"
#include "Asset_Texture.h"

using TileId = unsigned int;
using std::string;

enum Sheet { TileSize = 32, SheetWidth = 256, SheetHeight = 96 };

struct TileInfo
{
    // TODO Allow sprite to flip / rotate

    TileInfo(SharedContext *context, const string& texture = "", TileId id = 0):
        mContext(context),
        mId(id),
        mDeadly(false)
    {
        Asset_Texture* textureManager = mContext->mTextureManager;
        if(texture == "") {
            mId = id;
            return;
        }
        if(textureManager == nullptr) {
            return;
        }
        if(!textureManager->requireAsset(texture))
            return;
        mTexture = texture;
        mId = id;
        mSprite.setTexture(*textureManager->getAsset(mTexture));
        sf::IntRect tileBoundaries(
                    mId % (Sheet::SheetWidth / Sheet::TileSize) * Sheet::TileSize,
                    mId / (Sheet::SheetWidth / Sheet::TileSize) * Sheet::TileSize,
                    Sheet::TileSize,
                    Sheet::TileSize);
        mSprite.setTextureRect(tileBoundaries);
    }

    ~TileInfo()
    {
        if(mTexture == "")
            return;
        mContext->mTextureManager->releaseAsset(mTexture);
    }

    TileId mId;
    string mName;
    sf::Vector2f mFriction;
    bool mDeadly;

    SharedContext* mContext;
    string mTexture;

    sf::Sprite mSprite;
};

struct Tile
{
    TileInfo* mProperties;
    bool mWarp;
};

#endif // TILEINFO_H
