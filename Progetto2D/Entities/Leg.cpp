#include "../Headers/Leg.h"
#include "../Headers/QuadBuilder.h"

#include <cmath>

void Leg::loadComponents()
{

	Quad foot = QuadBuilder()
		.setLPosition(myCommon::vec3({ .75f, -20.0f , 0}))
		.setColor({ 0,0,0,1 })
		.setLScale({ 1,.1f,1 })
		.build();
	components.push_back(foot);
	Quad leg = QuadBuilder()
		.setLPosition(myCommon::vec3({0, -1, 0}))
		.setColor({ 0,0,0,1 })
		.setLScale({ .25f, 1,1 })
		.build();
	components.push_back(leg);
}

Leg::Leg(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	loadComponents();
}

void Leg::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight)
{
	if (entityName.compare("alt") == 0) {
		localRotation.z = sin(myCommon::degToRad(time * .25f)) * 20;
	}
	else {
		localRotation.z = -sin(myCommon::degToRad(time * .25f)) * 20;
	}
}
