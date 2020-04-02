#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using std::string;

enum class EntityType { Base, Enemy, Player };

enum class EntityState
{
    Idle, Walking, Jumping, Attacking, Hurt, Dying
};

struct TileInfo;
struct CollisionElement
{
    CollisionElement(float area, TileInfo* info, const sf::FloatRect& bounds):
        mArea(area),
        mTile(info),
        mTileBounds(bounds){}
    float mArea;
    TileInfo* mTile;
    sf::FloatRect mTileBounds;
};

using Collisions = std::vector<CollisionElement>;

/// Sort the collision ot resolve biggers collisions first
bool sortCollisions(const CollisionElement& c1, const CollisionElement& c2);

class EntityManager;
class EntityBase
{
    friend class EntityManager;

public:
    EntityBase(EntityManager* entityManager);
    virtual ~EntityBase();

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
    EntityState getState() const;
    string getName() const;
    unsigned int getId() const;
    EntityType getType() const;

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    void setSize(float x, float y);
    void setState(const EntityState& state);

    void move(float x, float y);

    void addVelocity(float x, float y);

    void accelerate(float x, float y);

    void setAcceleration(float x, float y);

    void applyFriction(float x, float y);

    virtual void update(float dt);

    virtual void draw(sf::RenderWindow* window) = 0;

protected:
    /// Entity name
    string mName;

    /// Entity tupe
    EntityType mType;

    /// Entity id in the entity manager.
    unsigned int mId;

    /// Current position.
    sf::Vector2f mPosition;

    /// Position before entity moved.
    sf::Vector2f mPositionOld;

    /// Current velocity.
    sf::Vector2f mVelocity;

    /// Maximum velocity.
    sf::Vector2f mMaxVelocity;

    /// Value of acceleration.
    sf::Vector2f mSpeed;

    /// Current acceleration.
    sf::Vector2f mAcceleration;

    /// Default friction value.
    sf::Vector2f mFriction;

    /// Tile underneath entity.
    TileInfo* mReferenceTile;

    /// Size of the collision box.
    sf::Vector2f mSize;

    /// The bounding box for collisions.
    sf::FloatRect mAABB;

    /// Current entity state.
    EntityState mState;

    /// Flags for remembering x-axis collisions.
    bool mCollidingOnX;

    /// Flags for remembering y-axis collisions.
    bool mCollidingOnY;

    ///
    Collisions mCollisions;

    /// Entity Manager access
    EntityManager* mEntityManager;


    void updateAABB();

    void checkCollisions();

    void resolveCollisions();

    /// What this entity does to the collider entity
    virtual void onEntityCollision(EntityBase* collider, bool attack) = 0;
};

#endif // ENTITY_BASE_H
