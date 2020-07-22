#pragma once
#include "common.h"
#include "IEntity.h"

class Patapon : public IEntity {
private:
	virtual void loadComponents() override;
	void init(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 scale, int layer, std::string meshName, std::string entityName);
	bool dead = false, cheering = false;
	float const defaultVelocityX = 200;
	float initialY = 0;
	myCommon::vec3 velocity = myCommon::vec3({ defaultVelocityX, 0, 0 });
public:
	Patapon(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight);
	Patapon(Patapon const& p);
	void signal(std::string const& message) override;
	virtual void onUpdate(int const time, float const deltatime, float const worldWidth, float const WorldHeight) override;
};