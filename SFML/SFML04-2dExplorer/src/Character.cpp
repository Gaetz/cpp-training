#include "Character.h"
#include "EntityManager.h"
#include "StateManager.h"
#include "SharedContext.h"

Character::Character(EntityManager* entityManager):
    EntityBase(entityManager),
    mSpriteSheet(mEntityManager->getContext()->mTextureManager),
    mJumpVelocity(250),
    mHp(5)
{
    mName = "Character";
}

Character::~Character()
{

}

void Character::move(const Direction& direction)
{
    if(getState() == EntityState::Dying)
        return;
    mSpriteSheet.setDirection(direction);
    if(direction == Direction::Left) {
        accelerate(-mSpeed.x, 0);
    } else {
        accelerate(mSpeed.x, 0);
    }
    if(getState() == EntityState::Idle) {
        setState(EntityState::Walking);
    }
}

void Character::jump()
{
    if(getState() == EntityState::Dying || getState() == EntityState::Jumping || getState() == EntityState::Hurt)
        return;
    setState(EntityState::Jumping);
    addVelocity(0, -mJumpVelocity);
}

void Character::attack()
{
    if(getState() == EntityState::Dying || getState() == EntityState::Jumping
            || getState() == EntityState::Hurt || getState() == EntityState::Attacking)
        return;
    setState(EntityState::Attacking);
    // EntityManager manages collisions
}

void Character::getHurt(const int& damage)
{
    if(getState() == EntityState::Dying || getState() == EntityState::Hurt)
        return;
    mHp = (mHp - damage > 0 ? mHp - damage : 0);
    if(mHp) {
        setState(EntityState::Hurt);
    } else {
        setState(EntityState::Dying);
    }
}

void Character::load(const std::string& path)
{
    std::ifstream file;
    file.open(Utils::getWorkingDirectory() + std::string("/assets/data/entities/") + path);
    if (!file.is_open()){ std::cout << "Failed loading the character file: " << path << std::endl; return; }
    std::string line;
    while(std::getline(file,line)){
        if (line[0] == '|'){ continue; }
        std::stringstream keystream(line);
        std::string type;
        keystream >> type;
        if(type == "Name"){
            keystream >> mName;
        } else if(type == "Spritesheet"){
            std::string path;
            keystream >> path;
            mSpriteSheet.loadSheet("assets/data/animations/" + path);
        } else if(type == "Hp"){
            keystream >> mHp;
        } else if(type == "BoundingBox"){
            sf::Vector2f boundingSize;
            keystream >> boundingSize.x >> boundingSize.y;
            setSize(boundingSize.x, boundingSize.y);
        } else if(type == "DamageBox"){
            keystream >> mAttackAABBoffset.x >> mAttackAABBoffset.y
                    >> mAttackAABB.width >> mAttackAABB.height;
        } else if(type == "Speed"){
            keystream >> mSpeed.x >> mSpeed.y;
        } else if(type == "JumpVelocity"){
            keystream >> mJumpVelocity;
        } else if(type == "MaxVelocity"){
            keystream >> mMaxVelocity.x >> mMaxVelocity.y;
        } else {
            std::cout << "Unknown type in character file: " << type << std::endl;
        }
    }
    file.close();
}

void Character::updateAttackAABB()
{
    mAttackAABB.left = (mSpriteSheet.getDirection() == Direction::Left ?
                            (mAABB.left - mAttackAABB.width) - mAttackAABBoffset.x : (mAABB.left + mAABB.width) + mAttackAABBoffset.x);
    mAttackAABB.top = mAABB.top + mAttackAABBoffset.y;
}

void Character::animate()
{
    EntityState state = getState();

    // Walk
    if(state == EntityState::Walking && mSpriteSheet.getCurrentAnim()->getName() != "Walk") {
        mSpriteSheet.setAnimation("Walk", true, true);
    }
    // Idle
    else if(state == EntityState::Idle && mSpriteSheet.getCurrentAnim()->getName() != "Idle") {
        mSpriteSheet.setAnimation("Idle", true, true);
    }
    // Jump
    else if(state == EntityState::Jumping && mSpriteSheet.getCurrentAnim()->getName() != "Jump") {
        mSpriteSheet.setAnimation("Jump", true, false);
    }
    // Attack
    else if(state == EntityState::Attacking && mSpriteSheet.getCurrentAnim()->getName() != "Attack") {
        mSpriteSheet.setAnimation("Attack", true, false);
    }
    // Being hurt
    else if(state == EntityState::Hurt && mSpriteSheet.getCurrentAnim()->getName() != "Hurt") {
        mSpriteSheet.setAnimation("Hurt", true, false);
    }
    // Dying
    else if(state == EntityState::Dying && mSpriteSheet.getCurrentAnim()->getName() != "Death") {
        mSpriteSheet.setAnimation("Death", true, false);
    }
}

void Character::update(float dt)
{
    EntityBase::update(dt);
    // Attack
    if(mAttackAABB.width != 0 && mAttackAABB.height != 0) {
        updateAttackAABB();
    }
    // State transition
    if(getState() != EntityState::Dying && getState() != EntityState::Attacking && getState() != EntityState::Hurt) {
        if(std::abs(mVelocity.y) >= 0.001f) {
            setState(EntityState::Jumping);
        } else if(std::abs(mVelocity.x) >= 0.1f) {
            setState(EntityState::Walking);
        } else {
            setState(EntityState::Idle);
        }
    } else if(getState() == EntityState::Attacking || getState() == EntityState::Hurt) {
        if(!mSpriteSheet.getCurrentAnim()->isPlaying()) {
            setState(EntityState::Idle);
        }
    } else if(getState() == EntityState::Dying) {
        if(!mSpriteSheet.getCurrentAnim()->isPlaying()) {
            mEntityManager->remove(mId);
        }
    }
    // Animation
    if(mSpriteSheet.getCurrentAnim())
    {
        animate();
        mSpriteSheet.update(dt);
        mSpriteSheet.setSpritePosition(mPosition);
    }
}

void Character::draw(sf::RenderWindow* window)
{
    mSpriteSheet.draw(window);
}
