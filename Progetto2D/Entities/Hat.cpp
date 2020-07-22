#include "..\Headers\Hat.h"
#include "../Headers/QuadBuilder.h"

void Hat::loadComponents()
{
	Quad feather = QuadBuilder()
		.setLScale({ .5f, 3.5f, 1 })
		.setLPosition({ -5.0f, .75f, 0})
		.setLRotation({ 0, 0, 10 })
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(feather);

	feather = QuadBuilder()
		.setLScale({ .5f, 3.5f, 1 })
		.setLPosition({ 5.0f, .75f, 0 })
		.setLRotation({ 0, 0, -10 })
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(feather);

	feather = QuadBuilder()
		.setLScale({ .5f, 3.5f, 1 })
		.setLPosition({ 0, .75f, 0 })
		.setLRotation({ 0, 0, 0 })
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(feather);

	Quad base = QuadBuilder()
		.setColor({ 0,0,0,1 })
		.setLScale({ 3.75f, .75f, 1 })
		.setLRotation({0, 0, 0})
		.build();
	components.push_back(base);
	
}


Hat::Hat(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeigth)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeigth)
{
	loadComponents();
	originalPos = coords;
}

void Hat::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight)
{
	absoluteGlobalRot.z = -sinf(myCommon::degToRad(time * .25f)) * 30;
}
