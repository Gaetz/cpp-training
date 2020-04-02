#include "EntityManager.h"
#include "SharedContext.h"

EntityManager::EntityManager(SharedContext *context, unsigned int maxEntities) :
	mContext(context),
	mMaxEntities(maxEntities),
	mIdCounter(0)
{
	loadEnemyTypes("enemies.list");
	registerEntity<Player>(EntityType::Player);
	registerEntity<Enemy>(EntityType::Enemy);
}

EntityManager::~EntityManager()
{
	purge();
}

SharedContext* EntityManager::getContext()
{
	return mContext;
}

int EntityManager::add(const EntityType &type, const std::string &name)
{
	auto itr = mEntityFactory.find(type);
	if (itr == mEntityFactory.end())
		return -1;
	EntityBase* entity = itr->second();
	entity->mId = mIdCounter;
	if (name != "")
		entity->mName = name;
	mEntities.emplace(mIdCounter, entity);
	// Enemy loading
	if (type == EntityType::Enemy) {
		auto itr = mEnemyTypes.find(name);
		if (itr != mEnemyTypes.end()) {
			Enemy* enemy = (Enemy*)entity;
			enemy->load(itr->second);
		}
	}

	++mIdCounter;
	return mIdCounter - 1; // return id, before incrementation =)
}

EntityBase* EntityManager::find(unsigned int id)
{
	auto itr = mEntities.find(id);
	if (itr == mEntities.end())
		return nullptr;
	return itr->second;
}

EntityBase* EntityManager::find(const std::string &name)
{
	for (auto &itr : mEntities) {
		if (itr.second->getName() == name) {
			return itr.second;
		}
	}
	return nullptr;
}

void EntityManager::remove(unsigned int id)
{
	mEntitiesToRemove.emplace_back(id);
}

void EntityManager::update(float dt)
{
	for (auto &itr : mEntities) {
		itr.second->update(dt);
	}
	entityCollisionCheck();
	processRemoval();
}

void EntityManager::draw()
{
	sf::RenderWindow* window = mContext->mWindow->getRenderWindow();
	sf::FloatRect viewSpace = mContext->mWindow->getViewSpace();
	// Draw only entities in viewSpace
	for (auto &itr : mEntities) {
		if (!viewSpace.intersects(itr.second->mAABB))
			continue;
		itr.second->draw(window);
	}
}

void EntityManager::entityCollisionCheck()
{
	if (mEntities.empty())
		return;
	for (auto itr = mEntities.begin(); std::next(itr) != mEntities.end(); ++itr) {
		for (auto itr2 = std::next(itr); itr2 != mEntities.end(); ++itr2) {
			if (itr->first == itr2->first)
				continue;
			// AABB bounding box collision
			if (itr->second->mAABB.intersects(itr2->second->mAABB)) {
				itr->second->onEntityCollision(itr2->second, false);
				itr2->second->onEntityCollision(itr->second, false);
			}
			// AABB attack collision, for Characters
			EntityType t1 = itr->second->getType();
			EntityType t2 = itr2->second->getType();
			if (t1 == EntityType::Player || t1 == EntityType::Enemy) {
				Character* c1 = (Character*)itr->second;
				if (c1->mAttackAABB.intersects(itr2->second->mAABB)) {
					c1->onEntityCollision(itr2->second, true);
				}
			}
			if (t2 == EntityType::Player || t2 == EntityType::Enemy) {
				Character* c2 = (Character*)itr2->second;
				if (c2->mAttackAABB.intersects(itr->second->mAABB)) {
					c2->onEntityCollision(itr->second, true);
				}
			}
		}
	}
	// Could use binary space partitionning, but would be overkill
}

void EntityManager::loadEnemyTypes(const std::string &name)
{
	std::ifstream file;
	file.open(Utils::getWorkingDirectory() + std::string("assets/data/entities/") + name);
	if (file.is_open()) {
		string line;
		while (std::getline(file, line)) {
			if (line[0] == '|') // Descriptive line
				continue;
			std::stringstream keystream(line);
			string name;
			string charFile;
			keystream >> name >> charFile;
			mEnemyTypes.emplace(name, charFile);
		}
		file.close();
	}
}

void EntityManager::purge()
{
	if (!mEntities.empty()) {
		for (auto &itr : mEntities) {
			delete itr.second;
			itr.second = nullptr;
		}
		mEntities.clear();
	}
	mIdCounter = 0;
}

void EntityManager::processRemoval()
{
	while (mEntitiesToRemove.begin() != mEntitiesToRemove.end()) {
		unsigned int id = mEntitiesToRemove.back();
		auto itr = mEntities.find(id);
		if (itr != mEntities.end()) {
			delete itr->second;
			mEntities.erase(itr);
		}
		mEntitiesToRemove.pop_back();
	}
}
