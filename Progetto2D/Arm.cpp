#include "Headers\Arm.h"
#include "Headers/CircleBuilder.h"

void Arm::loadComponents()
{
	//arm
	Circle c = CircleBuilder()
		.setColor({ 0, 0, 0, 1 })
		.setLPosition({.7f, 0, 0})
		.setDrawMode(myCommon::DrawMode::triangles_strip)
		.setAngle(3.14159265358979323846f)
		.build();
	components.push_back(c);
	//hand
	c = CircleBuilder()
		.setLScale({ .25f, .25f, 1 })
		.setColor({ 0, 0, 0, 1 })
		.setLPosition( myCommon::vec3({ 6.5, -.2f, 0 }) )
		.build();
	components.push_back(c);
}



Arm::Arm(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	loadComponents();
}

void Arm::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight) {
	absoluteGlobalRot.z = sinf(myCommon::degToRad(time * .25f)) * 15;
}
