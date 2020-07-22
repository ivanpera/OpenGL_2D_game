#pragma once
#include "common.h"
#include "IEntity.h"

class Background : public IEntity {
private:
	virtual void loadComponents() override;
public:
	Background(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight);
};