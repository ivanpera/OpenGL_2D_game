#include "..\Headers\IEntity.h"
#include "..\Headers\Eyeball.h"
#include "../Headers/CircleBuilder.h"
#include <string>
using namespace myCommon;

Eyeball::Eyeball(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	loadComponents();
}

void Eyeball::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight)
{
	localRotation.z = -sinf(myCommon::degToRad(time * .25f)) * 20;
}

void Eyeball::loadComponents()
{
	//Outer black circle
	Circle c = CircleBuilder()
		.setLScale({1, 1, 1})
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(c);

	//Inner white circle
	c = CircleBuilder()
		.setLPosition({0, .05f, 0})
		.setLScale({ .8f,.8f,1.0f })
		.setColor({ 1,1,1,1 })
		.build();
	components.push_back(c);

	//Inner black circle
	c = CircleBuilder()
		.setLPosition({ 0, 0, 0 })
		.setLScale({ .4f,.4f,1 })
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(c);
}


