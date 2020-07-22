#pragma once
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <deque>
#include "IEntity.h"
#include "EntitiesKey.h"
#include "common.h"

enum class KeyPosition {
	Left, Over, Right, Under, Inside
};

enum class GameState {
	Pause, Playing, Over
};

class World {
private:
	std::multimap<EntityKey, std::shared_ptr<IEntity>> entities;
	std::deque<std::shared_ptr<IEntity>> keys;
	std::deque<std::shared_ptr<IEntity>> patapons;
	std::shared_ptr<IEntity> activationBox;
	std::map<std::string, std::shared_ptr<IEntity>> referenceEntities;
	unsigned int score = 0, lives;
	unsigned int worldW, worldH;
	GameState gameState = GameState::Pause;
	template<class T>
	void addEntity(T const& entity) {
		using namespace std;
		EntityKey k{ entity.layer, entity.getMeshName() };
		this->entities.insert({ k, shared_ptr<T>(new T(entity)) });
	}
	template<class T>
	void addEntity(std::shared_ptr<T> const& pEntity) {
		using namespace std;
		EntityKey k{ (*pEntity).layer, (*pEntity).getMeshName() };
		this->entities.insert({ k, pEntity });
	}
	template<class T>
	void addReferenceEntity(T const& entity, std::string const& key) {
		using namespace std;
		this->referenceEntities.insert({ key, shared_ptr<T>(new T(entity)) });
	}
	void spawnKey();
	void loseLife();
	void attemptKey(float targetAngle);
	std::pair<KeyPosition,KeyPosition> keyInArea(IEntity const& key);
	float spawnTimer = 1500;
	float oldSpawn = 0;
public:
	World(unsigned int const lives, unsigned int const width, unsigned int const height);
	unsigned int getLives() const;
	unsigned int getScore() const;
	void addToLives(int const value);
	void addToScore(int const value);
	std::multimap<EntityKey, std::shared_ptr<IEntity>> getEntities() const;
	void onKeyDown(unsigned char key);
	void update(int const time, float const deltaTime);

};
