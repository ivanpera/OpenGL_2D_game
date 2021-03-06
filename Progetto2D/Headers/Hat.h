#pragma once
#include "common.h"
#include "IEntity.h"

class Hat : public IEntity {
private:
	virtual void loadComponents() override;
	myCommon::vec3 originalPos;
public:
	Hat(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeigth);
	virtual void onUpdate(int const time, float const deltatime, float const worldWidth, float const WorldHeight) override;
};