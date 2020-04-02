#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <array>
#include <fstream>
#include <sstream>
#include "../utils/utilities.h"
#include "../core/shared_context.h"
#include "../states/state_base.h"
#include "tile_info.h"

using TileId = unsigned int;
using std::string;

// TODO replace by std::array or preallocated std::vector to get faster access
using TileMap = std::unordered_map<TileId, Tile*>;
using TileSet = std::unordered_map<TileId, TileInfo*>;

class Map
{
public:
    Map(SharedContext* context, BaseState* currentState);

    ~Map();

    TileInfo* getDefaultTile();
    float getGravity() const;
    unsigned int getTileSize() const;
    const sf::Vector2u& getMapSize() const;
    const sf::Vector2f& getPlayerStart() const;
    int getPlayerId() const;

    Tile* getTile(unsigned int x, unsigned int y, unsigned int layer);
    void loadMap(const string& path);
    void loadNextMap();

    void update(float dt);
    void draw(unsigned int layer);

private:
    TileSet mTileSet;
    TileMap mTileMap;
    sf::Sprite mBackground;
    string mBackgroundTexture;
    TileInfo mDefaultTile;

    sf::Vector2u mMaxMapSize;
    sf::Vector2f mPlayerStart;
    unsigned int mTileCount;
    unsigned int mTileSetCount;
    float mMapGravity;
    int mPlayerId;

    string mNextMap;
    bool mLoadNextMap;
    BaseState* mCurrentState;
    SharedContext* mContext;

    void loadTiles(const string& path);
    void purgeMap();
    void purgeTileSet();

    /// Convert 2D coordinates to 1D ints.
    unsigned int convertCoords(unsigned int x, unsigned int y, unsigned int layer) const;
};

#endif // MAP_H
