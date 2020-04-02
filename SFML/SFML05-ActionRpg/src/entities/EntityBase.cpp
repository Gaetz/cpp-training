//#include "EntityBase.h"
//#include "../core/EntityManager.h"
//#include "../core/SharedContext.h"
//#include "../display/Map.h"

//bool sortCollisions(const CollisionElement &c1, const CollisionElement &c2)
//{
//    return c1.mArea > c2.mArea;
//}

//EntityBase::EntityBase(EntityManager *entityManager):
//    mEntityManager(entityManager),
//    mName("BaseEntity"),
//    mType(EntityType::Base),
//    mReferenceTile(nullptr),
//    mState(EntityState::Idle),
//    mId(0),
//    mCollidingOnX(false),
//    mCollidingOnY(false) {}

//EntityBase::~EntityBase() {}

//const sf::Vector2f& EntityBase::getSize() const { return mSize; }
//std::string EntityBase::getName()  const  { return mName; }
//EntityState EntityBase::getState() const { return mState; }
//unsigned int EntityBase::getId() const { return mId; }
//EntityType EntityBase::getType() const { return mType; }
//const sf::Vector2f& EntityBase::getPosition() const { return mPosition; }

//void EntityBase::setPosition(float x, float y)
//{
//    mPosition = sf::Vector2f(x,y);
//    updateAABB();
//}

//void EntityBase::setPosition( const  sf::Vector2f& position)
//{
//    mPosition = position;
//    updateAABB();
//}

//void EntityBase::setSize(float x, float y)
//{
//    mSize = sf::Vector2f(x,y);
//    updateAABB();
//}

//void EntityBase::setAcceleration(float x, float y)
//{
//    mAcceleration = sf::Vector2f(x, y);
//}

//void EntityBase::setState( const  EntityState& state)
//{
//    if (mState == EntityState::Dying){ return; }
//    mState = state;
//}

//void EntityBase::move(float x, float y)
//{
//    mPositionOld = mPosition;
//    mPosition += sf::Vector2f(x, y);

//    // Dont get out of screen, die under bottom of screen
//    sf::Vector2u mapSize = mEntityManager->getContext()->mGameMap->getMapSize();
//    // Horizontal position check
//    if(mPosition.x < 0) {
//        mPosition.x = 0;
//    } else if (mPosition.x > (mapSize.x + 1) * Sheet::TileSize) {
//        mPosition.x = (mapSize.x + 1) * Sheet::TileSize;
//    }
//    // Vertical position check
//    if(mPosition.y < 0) {
//        mPosition.y = 0;
//    } else if (mPosition.y > (mapSize.y + 1) * Sheet::TileSize) {
//        mPosition.y = (mapSize.y + 1) * Sheet::TileSize;
//        // Fall into a pit
//        setState(EntityState::Dying);
//    }

//    // Update collision mask
//    updateAABB();
//}

//void EntityBase::addVelocity(float x, float y)
//{
//    mVelocity += sf::Vector2f(x, y);

//    // Ceil to max velocity
//    if(std::abs(mVelocity.x) > mMaxVelocity.x) {
//        if(mVelocity.x < 0) {
//            mVelocity.x = -mMaxVelocity.x;
//        } else {
//            mVelocity.x = mMaxVelocity.x;
//        }
//    }
//    if(std::abs(mVelocity.y) > mMaxVelocity.y) {
//        if(mVelocity.y < 0) {
//            mVelocity.y = -mMaxVelocity.y;
//        } else {
//            mVelocity.y = mMaxVelocity.y;
//        }
//    }
//}

//void EntityBase::accelerate(float x, float y)
//{
//    mAcceleration += sf::Vector2f(x, y);
//}

//void EntityBase::applyFriction(float x, float y)
//{
//    if(mVelocity.x != 0) {
//        if(std::abs(mVelocity.x) - std::abs(x) < 0) {
//            mVelocity.x = 0;
//        } else {
//            if (mVelocity.x < 0) {
//                mVelocity.x += x;
//            } else {
//                mVelocity.x -= x;
//            }
//        }
//    }
//    if(mVelocity.y != 0) {
//        if(std::abs(mVelocity.y) - std::abs(y) < 0) {
//            mVelocity.y = 0;
//        } else {
//            if (mVelocity.y < 0) {
//                mVelocity.y += y;
//            } else {
//                mVelocity.y -= y;
//            }
//        }
//    }
//}

//void EntityBase::update(float dt)
//{
//    // Acceleration from gravity
//    Map* map = mEntityManager->getContext()->mGameMap;
//    float gravity = map->getGravity();
//    accelerate(0, gravity);
//    addVelocity(mAcceleration.x * dt, mAcceleration.y * dt);
//    setAcceleration(0.0f, 0.0f);

//    // Friction (and manage deadly tile by the way)
//    sf::Vector2f frictionValue;
//    if(mReferenceTile) {
//        frictionValue = mReferenceTile->mFriction;
//        if(mReferenceTile->mDeadly) {
//            setState(EntityState::Dying);
//        }
//    } else if (map->getDefaultTile()) {
//        frictionValue = map->getDefaultTile()->mFriction;
//    } else {
//        frictionValue = mFriction;
//    }
//    float frictionX = (mSpeed.x * frictionValue.x) * dt; // Speed implemented in derived class
//    float frictionY = (mSpeed.y * frictionValue.y) * dt;
//    applyFriction(frictionX, frictionY);

//    // Move
//    sf::Vector2f deltaPosition = mVelocity * dt;
//    move(deltaPosition.x, deltaPosition.y);

//    // Collisions
//    mCollidingOnX = false;
//    mCollidingOnY = false;
//    checkCollisions();
//    resolveCollisions();
//}

//void EntityBase::updateAABB()
//{
//    mAABB = sf::FloatRect(mPosition.x - (mSize.x / 2),
//                          mPosition.y - mSize.y,
//                          mSize.x, mSize.y);
//}

//void EntityBase::checkCollisions()
//{
//    Map* map = mEntityManager->getContext()->mGameMap;
//    unsigned int tileSize = map->getTileSize();
//    int fromX = floor(mAABB.left / tileSize);
//    int toX = floor((mAABB.left + mAABB.width) / tileSize);
//    int fromY = floor(mAABB.top / tileSize);
//    int toY = floor((mAABB.top + mAABB.height) / tileSize);

//    for(int x = fromX; x <= toX; ++x) {
//        for(int y = fromY; y <= toY; ++y) {
//            Tile* tile = map->getTile(x, y);
//            if(!tile)
//                continue;
//            sf::FloatRect tileBounds(x * tileSize, y * tileSize, tileSize, tileSize);
//            sf::FloatRect intersection;
//            mAABB.intersects(tileBounds, intersection); // Set intersection
//            float area = intersection.width * intersection.height;

//            CollisionElement e(area, tile->mProperties, tileBounds);
//            mCollisions.emplace_back(e);

//            // Collision with warp, go to next nevel
//            if(tile->mWarp && mType == EntityType::Player) {
//                map->loadNextMap();
//            }
//        }
//    }
//}

//void EntityBase::resolveCollisions()
//{
//    if(!mCollisions.empty()) {
//        std::sort(mCollisions.begin(), mCollisions.end(), sortCollisions);
//        Map* gameMap = mEntityManager->getContext()->mGameMap;
//        unsigned int tileSize = gameMap->getTileSize();
//        for(auto &itr : mCollisions) {
//            if(!mAABB.intersects(itr.mTileBounds)) {
//                continue;
//            }
//            // Distances from the center of the entity's bounding box to the center of the tile's bounding box
//            float xDiff = (mAABB.left + (mAABB.width / 2)) - (itr.mTileBounds.left + (itr.mTileBounds.width / 2));
//            float yDiff = (mAABB.top + (mAABB.height / 2)) - (itr.mTileBounds.top + (itr.mTileBounds.height / 2));
//            float resolve = 0;
//            // Biggest collision resolved
//            if(std::abs(xDiff) > std::abs(yDiff)) {
//                // Entity is right side of the tile
//                if(xDiff > 0) {
//                    resolve = (itr.mTileBounds.left + tileSize) - mAABB.left;
//                // Entity is left side of the tile
//                } else {
//                    resolve = -((mAABB.left + mAABB.width) - itr.mTileBounds.left);
//                }
//                move(resolve, 0);
//                mVelocity.x = 0;
//                mCollidingOnX = true;
//            } else {
//                if(yDiff > 0) {
//                    resolve = (itr.mTileBounds.top + tileSize) - mAABB.top;
//                } else {
//                    resolve = -((mAABB.top + mAABB.height) - itr.mTileBounds.top);
//                }
//                move(0, resolve);
//                mVelocity.y = 0;
//                if(mCollidingOnY)
//                    continue;
//                mReferenceTile = itr.mTile;
//                mCollidingOnY = true;
//            }
//        }
//        mCollisions.clear();
//    }
//    if(!mCollidingOnY) {
//        mReferenceTile = nullptr;
//    }
//}
