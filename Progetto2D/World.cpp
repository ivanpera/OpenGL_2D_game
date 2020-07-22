#include "Headers/World.h"
#include "Headers/PataponBuilder.h"
#include "Headers/KeyBuilder.h"
#include "Headers/BgBuilder.h"
#include "Headers/ABoxBuilder.h"
#include <ctime>
using namespace std;


World::World(unsigned int const lives, unsigned int const width, unsigned int const height) : lives(lives) {
	using namespace myCommon;
	worldW = width;
	worldH = height;

	float fw = (float)worldW, fh = (float)worldH;

	//Entities initialization
	//NOTE: entities with children need to define their copy constructor if they want to have access to overridden methods such as update and don't want to mess up the pointer to the parent

	std::srand(std::time(0));
	addReferenceEntity(PataponBuilder().setLayer(1).setMeshName("Patapon").setTag("Patapon").build(), "Patapon");
	auto& kk = (*referenceEntities.at("Patapon"));
	//spawn as many patapons as lives
	for (unsigned int i = 0; i < lives; i++) {
		float direction = std::rand() % 2 ? -1.0f : 1.0f;
		float facing = std::rand() % 2 ? 0.0f : 180.0f;
		float spawnX = (float)(std::rand() % worldW) * .5f;
		float scaleY = 1.0f;
		addEntity(PataponBuilder().setPostion({ direction * spawnX,kk.getHeight() * scaleY,0 }).setLocalRotation({ 0,facing,0 }).setScale({ 1.0f,scaleY,1 }).setLayer(kk.layer).setMeshName(kk.getMeshName()).build());
		auto range = entities.equal_range({ kk.layer, kk.getMeshName() });
		patapons.push_back((--range.second)->second);
	}
	addReferenceEntity(KeyBuilder().setPostion({ -fw, -fh / 4, 0 }).setLayer(3).setMeshName("Key").build(), "KeyUp");
	addReferenceEntity(KeyBuilder().setPostion({ -fw, -fh / 4, 0 }).setLayer(3).setLocalRotation({0,0,-90}).setMeshName("Key").build(), "KeyRight");
	addReferenceEntity(KeyBuilder().setPostion({ -fw, -fh / 4, 0 }).setLayer(3).setLocalRotation({ 0,0,-180 }).setMeshName("Key").build(), "KeyDown");
	addReferenceEntity(KeyBuilder().setPostion({ -fw, -fh / 4, 0 }).setLayer(3).setLocalRotation({ 0,0,-270 }).setMeshName("Key").build(), "KeyLeft");
	addEntity(BackgroundBuilder().setAbsWidth(fw).setAbsHeigth(fh).setMeshName("Bg").build());
	addEntity(ABoxBuilder().setPostion({ 0,-fh / 4,0 }).setLayer(2).setMeshName("ABox").build());
	auto it = entities.find({ 2, "ABox"});
	activationBox = shared_ptr<IEntity>(&(*(*it).second));
}


unsigned int World::getLives() const
{
	return this->lives;
}

unsigned int World::getScore() const
{
	return this->score;
}

void World::addToLives(int const value)
{
	this->lives += value;
}

void World::addToScore(int const value)
{
	this->score += value;
}

std::multimap<EntityKey, std::shared_ptr<IEntity>> World::getEntities() const
{
	return this->entities;
}

void World::attemptKey(float targetAngle) {
	bool ok = false;
	if (keys.size() <= 0) {
		return;
	}
	IEntity& firstKey = *keys.front();
	if (firstKey.getPosition().x + firstKey.getWidth() * .5 <= -(worldW * .5f)) {
		return;
	}
	if (keyInArea(firstKey).first == keyInArea(firstKey).second) {
		ok = firstKey.localRotation.z == targetAngle;
	}
	keys.pop_front();
	if (ok) {
		firstKey.signal("ok");
		int ncheer = std::rand() % patapons.size() + 1;
		for (int i = 0; i < ncheer; i++) {
			patapons.at(i)->signal("cheer");
		}
	}
	else {
		firstKey.signal("ko");
		loseLife();
	}
}

void World::onKeyDown(unsigned char key) {
	if (gameState == GameState::Over) {
		return;
	}
	switch (key) {
	case 'u':
		attemptKey(0);
		break;
	case 'r':
		attemptKey(-90);
		break;
	case 'd':
		attemptKey(-180);
		break;
	case 'l':
		attemptKey(-270);
		break;
	//SPACEBAR
	case 32:
		if (gameState == GameState::Playing) {
			gameState = GameState::Pause;
		}
		else if (gameState == GameState::Pause) {
			gameState = GameState::Playing;
		}
		return;
	default:
		return;
	}
}

void World::update(int const time, float const deltaTime)
{
	//if it's time, spawn entities
	if (gameState == GameState::Pause) {
		return;
	}
	if (gameState != GameState::Over) {
		oldSpawn += deltaTime * 1000;
		if (oldSpawn >= spawnTimer) {
			spawnTimer = spawnTimer <= 500 ? spawnTimer : spawnTimer  - 25;
			spawnKey();
			oldSpawn = 0;
		}
	}
	for (auto it = entities.begin(); it != entities.end(); ) {
		auto& entity = (*(*it).second);
		entity.onUpdate(time, deltaTime, (float)worldW, (float)worldH);
		if (entity.getPosition().y + entity.getHeight() <= -(worldH * .5f) && !entity.getEntityName()._Equal("Background")) {
			it = entities.erase(it);
		}
		if (entity.getMeshName()._Equal("Key")) {
			if (keyInArea(entity).first == KeyPosition::Right) {
				if (!keys.empty()) {
					if (entity == *keys.front()) {
						keys.pop_front();
						entity.signal("ko");
						loseLife();
					}
				}
			}
			if (keyInArea(entity).first == keyInArea(entity).second) {
				entity.signal("lit");
			}
			//In this case the entirety of the key shape must be out of the activation area
			if (entity.getPosition().x - entity.getWidth() >= worldW * 0.5f || entity.getPosition().y >= 0) {
				it = entities.erase(it);
			}
			else {
				++it;
			}
		}
		else {
			if (it != entities.end()) {
				++it;
			}
		}
	}
}

pair<KeyPosition,KeyPosition> World::keyInArea(IEntity const& key) {
	float limitX = (*activationBox).getPosition().x + (*activationBox).getWidth() * .5f;
	float limitY = (*activationBox).getPosition().y -((*activationBox).getHeight() * .5f);
	float keyPosX = key.getPosition().x, keyPosY = key.getPosition().y;
	KeyPosition collisionX = keyPosX < -limitX ? KeyPosition::Left : keyPosX > limitX ? KeyPosition::Right : KeyPosition::Inside;
	KeyPosition collisionY = keyPosY < limitY ? KeyPosition::Under : keyPosY > limitY + ((*activationBox).getHeight()) ? KeyPosition::Over : KeyPosition::Inside;
	return { collisionX, collisionY };
}

void World::spawnKey()
{
	int r = std::rand() % 4;
	IEntity* k;
	switch (r)
	{
	case 0:
		k = &(*referenceEntities.at("KeyUp"));
		break;
	case 1:
		k = &(*referenceEntities.at("KeyRight"));
		break;
	case 2:
		k = &(*referenceEntities.at("KeyDown"));
		break;
	case 3:
		k = &(*referenceEntities.at("KeyLeft"));
		break;
	default:
		throw "No";
		break;
	}
	auto& kk = *k;
	
	addEntity(KeyBuilder().setPostion(kk.getPosition()).setRotation(kk.absoluteGlobalRot).setLocalRotation(kk.localRotation).setScale(kk.localScale).setLayer(kk.layer).setMeshName(kk.getMeshName()).build());
	auto range = entities.equal_range({ kk.layer, kk.getMeshName() });
	//Pushes the last key inserted in entities
	keys.push_back((--range.second)->second);
}

void World::loseLife()
{
	if (!patapons.empty()) {
		(*patapons.front()).signal("die");
		patapons.pop_front();
		lives--;
	}
	if (lives <= 0) {
		gameState = GameState::Over;
	}
}


