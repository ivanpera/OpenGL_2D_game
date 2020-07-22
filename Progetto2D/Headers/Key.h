#pragma once
#include "common.h"
#include "IEntity.h"


class Key : public IEntity {
private:
	virtual void loadComponents() override;
	bool dissolve = false;
	float scaleFactor;
	myCommon::vec3 velocity = { 400,0,0 };
public:
	void init(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 scale, int layer, std::string meshName, std::string entityName);
	Key(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight);
	Key(Key const& p);
	virtual void onUpdate(int const time, float const deltatime, float const worldWidth, float const WorldHeight) override;
	virtual void signal(std::string const& message) override;
};