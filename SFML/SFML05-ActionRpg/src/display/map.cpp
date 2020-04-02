#include "map.h"
#include "../core/state_manager.h"

Map::Map(SharedContext *context, BaseState *currentState) :
    mContext(context),
    mDefaultTile(context),
    mMaxMapSize(32, 32),
    mTileCount(0),
    mTileSetCount(0),
    mMapGravity(512.0f),
    mLoadNextMap(false),
    mCurrentState(currentState)
{
    mContext->mGameMap = this;
    loadTiles("assets/data/config/tiles.cfg");
}

Map::~Map()
{
    purgeMap();
    purgeTileSet();
    mContext->mGameMap = nullptr;
}

TileInfo* Map::getDefaultTile() { return &mDefaultTile; }
float Map::getGravity() const { return mMapGravity; }
unsigned int Map::getTileSize() const { return Sheet::TileSize; }
const sf::Vector2u& Map::getMapSize() const { return mMaxMapSize; }
const sf::Vector2f& Map::getPlayerStart() const { return mPlayerStart; }
int Map::getPlayerId() const { return mPlayerId; }

Tile* Map::getTile(unsigned int x, unsigned int y, unsigned int layer)
{
    if(x >= mMaxMapSize.x || y >= mMaxMapSize.y || layer >= Sheet::NumLayer)
        return nullptr;

    auto itr = mTileMap.find(convertCoords(x, y, layer));
    if(itr == mTileMap.end()) return nullptr;
    return itr->second;
}

unsigned int Map::convertCoords(unsigned int x, unsigned int y, unsigned int layer) const
{
    return (layer * mMaxMapSize.y + y) * mMaxMapSize.x + x;
}

void Map::loadTiles(const std::string &path)
{
    std::ifstream file;
    file.open(Utils::getWorkingDirectory() + path);
    if(!file.is_open()) {
        std::cout << "Failed loading tileset file: " << path << std::endl;
        return;
    }
    string line;
    while(std::getline(file, line)) {
        if(line[0] == '|')
            continue;
        std::stringstream keystream(line);
        int tileId;
        keystream >> tileId;
        if(tileId < 0)
            continue;
        TileInfo* tile = new TileInfo(mContext, "Tileset", tileId);
        keystream >> tile->mName >> tile->mFriction.x >> tile->mFriction.y >> tile->mDeadly;
        if(!mTileSet.emplace(tileId, tile).second) {
            std::cout << "Duplicate tile type: " << tile->mName << std::endl;
            delete tile;
        }
    }
    file.close();
}

void Map::loadMap(const std::string &path)
{
    std::ifstream file;
    file.open(Utils::getWorkingDirectory() + path);
    if(!file.is_open()) {
        std::cout << "Failed loading map file: " << path << std::endl;
        return;
    }
    EntityManager* entityManager = mContext->mEntityManager;
    string line;
    int playerId = -1;
    while(std::getline(file, line)) {
        if(line[0] == '|')
            continue;
        std::stringstream keystream(line);
        string type;
        keystream >> type;
        // Setup a tile
        if(type == "TILE") {
            // Get tile id
            int tileId = 0;
            keystream >> tileId;
            if(tileId < 0) {
                std::cout << "Bad tile id: " << tileId << std::endl;
                continue;
            }
            auto itr = mTileSet.find(tileId);
            if(itr == mTileSet.end()) {
                std::cout << "Tile id(" << tileId << ") was not found in tileset." << std::endl;
                continue;
            }
            // Get tile coords
            sf::Vector2i tileCoords;
            unsigned int tileLayer = 0;
            unsigned int tileSolidity = 0;
            keystream >> tileCoords.x >> tileCoords.y >> tileLayer >> tileSolidity;
            if(tileCoords.x > mMaxMapSize.x || tileCoords.y > mMaxMapSize.y || tileLayer >= Sheet::NumLayer) {
                std::cout << "Tile id(" << tileId << ") is out of range: " << tileCoords.x << " " << tileCoords.y << " " << tileLayer << std::endl;
                continue;
            }
            Tile* tile = new Tile();
            tile->mProperties = itr->second;
            tile->mSolid = (bool)tileSolidity;
            if(!mTileMap.emplace(convertCoords(tileCoords.x, tileCoords.y, tileLayer), tile).second) // Populate TileMap
            {
                std::cout << "Duplicate tile at coords: " << tileCoords.x << " " << tileCoords.y << " " << tileLayer << std::endl;
                delete tile;
                tile = nullptr;
                continue;
            }
            // Get warp
            string warp;
            keystream >> warp;
            tile->mWarp = false;
            if(warp == "WARP") {
                tile->mWarp = true;
            }
        }
        // Load background
        else if(type == "BACKGROUND") {
            if(mBackgroundTexture != "")
                continue;
            keystream >> mBackgroundTexture;
            if(!mContext->mTextureManager->requireAsset(mBackgroundTexture)) {
                mBackgroundTexture = "";
                continue;
            }
            sf::Texture* texture = mContext->mTextureManager->getAsset(mBackgroundTexture);
            mBackground.setTexture(*texture);
            // Fit background to window by scaling texture
            sf::Vector2f viewSize = mCurrentState->getView().getSize();
            sf::Vector2u textureSize = texture->getSize();
            sf::Vector2f scaleFactors;
            scaleFactors.x = viewSize.x / textureSize.x;
            scaleFactors.y = viewSize.y / textureSize.y;
            mBackground.setScale(scaleFactors);
        }
        // Map size
        else if(type == "SIZE") {
            keystream >> mMaxMapSize.x >> mMaxMapSize.y;
        }
        // Map gravity
        else if(type == "GRAVITY") {
            keystream >> mMapGravity;
        }
        // Default tile friction
        else if(type == "DEFAULT_FRICTION") {
            keystream >> mDefaultTile.mFriction.x >> mDefaultTile.mFriction.y;
        } // Next map file
        else if(type == "NEXTMAP") {
            keystream >> mNextMap;
        }
        // Player entity position
        else if(type == "ENTITY") {
            std::string name;
            keystream >> name;
            if(name == "Player" && mPlayerId != -1)
                continue;
            int entityId = mContext->mEntityManager->addEntity(name);
            if(entityId < 0)
                continue;
            if(name == "player") {
                mPlayerId = entityId;
            }
            C_Base* position = mContext->mEntityManager->getComponent<C_Position>(entityId, Component::Position);
            if(position) {
                keystream >> *position;
            }
        }
        // Default
        else {
            std::cout << "Map loading: unknown type \"" << type << "\"." << std::endl;
        }
    }
    file.close();
}

void Map::loadNextMap()
{
    mLoadNextMap = true;
}

void Map::update(float dt)
{
    if(mLoadNextMap) {
        purgeMap();
        mLoadNextMap = false;
        if(mNextMap != "") {
            loadMap("assets/data/maps/" + mNextMap);
        } else {
            mCurrentState->getStateManager()->switchTo(StateType::GameOver);
        }
        mNextMap = "";
    }
    sf::FloatRect viewSpace = mContext->mWindow->getViewSpace();
    mBackground.setPosition(viewSpace.left, viewSpace.top);
}

void Map::draw(unsigned int layer)
{
    if(layer >= Sheet::NumLayer)
        return;
    sf::RenderWindow* window = mContext->mWindow->getRenderWindow();
    //window->draw(mBackground);
    // TODO reimplement background
    sf::FloatRect viewSpace = mContext->mWindow->getViewSpace();
    // Culling: only tiles inside this rectangle will be drawned
    sf::Vector2i tileBegin(
                floor(viewSpace.left / Sheet::TileSize),
                floor(viewSpace.top / Sheet::TileSize));
    sf::Vector2i tileEnd(
                ceil((viewSpace.left + viewSpace.width) / Sheet::TileSize),
                ceil((viewSpace.top + viewSpace.height) / Sheet::TileSize));

    unsigned int count = 0;
    for(int x = tileBegin.x; x <= tileEnd.x; ++x) {
        for(int y = tileBegin.y; y <= tileEnd.y; ++y) {
            if(x < 0 || y < 0)
                continue;
            Tile* tile = getTile(x, y, layer);
            if(!tile)
                continue;
            sf::Sprite& sprite = tile->mProperties->mSprite;
            sprite.setPosition(x * Sheet::TileSize, y * Sheet::TileSize);
            // TODO set rotation and symetry
            window->draw(sprite);
            ++count;
        }
    }
}

void Map::purgeMap()
{
    mTileCount = 0;
    for (auto &itr : mTileMap) {
        delete itr.second;
    }
    mTileMap.clear();
    mContext->mEntityManager->purge();

    if(mBackgroundTexture == "")
        return;
    mContext->mTextureManager->releaseAsset(mBackgroundTexture);
    mBackgroundTexture = "";
}

void Map::purgeTileSet()
{
    for(auto &itr: mTileSet) {
        delete itr.second;
    }
    mTileSet.clear();
    mTileSetCount = 0;
}
