#include "..\Headers\Patapon.h"
#include "../Headers/EyeballBuilder.h"
#include "../Headers/HatBuilder.h"
#include "../Headers/LegBuilder.h"
#include "../Headers/ArmBuilder.h"
#include "../Headers/EyeballBuilder.h"
#include <cmath>

void Patapon::loadComponents()
{
	Eyeball body = EyeballBuilder()
		.setAbsHeigth(50.4f)
		.setAbsWidth(50.4f)
		.setParent(*this)
		.build();
	Hat hat = HatBuilder()
		.setAbsHeigth(7)
		.setAbsWidth(7)
		.setLayer(1)
		.setPostion({ 0,50,0 })
		.setParent(*this).build();
	Arm armR = ArmBuilder()
		.setPostion({ 50.4f,0,0 })
		.setLocalRotation({ 180,0,0 })
		.setParent(*this)
		.setAbsHeigth(24.5f)
		.setAbsWidth(28).build();
	Arm armL = ArmBuilder()
		.setPostion({ 50.4f,0,0 })
		.setLocalRotation({0,180,0})
		.setParent(*this)
		.setAbsHeigth(24.5f)
		.setAbsWidth(28).build();
	Leg legR = LegBuilder()
		.setPostion({ 15.0f, -47, 0 })
		.setParent(*this)
		.setAbsHeigth(28)
		.setAbsWidth(14)
		.build();
	Leg legL = LegBuilder()
		.setPostion({ -15.0f, -47, 0 })
		.setAbsHeigth(28)
		.setAbsWidth(14)
		.setParent(*this)
		.setTag("alt")
		.build();
	loadEntity(legR);
	loadEntity(legL);
	loadEntity(armL);
	loadEntity(armR);
	loadEntity(hat);
	loadEntity(body);
}

void Patapon::init(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 scale, int layer, std::string meshName, std::string entityName) {
	loadComponents();
	absoluteWidth = 106.4f;
	absoluteHeight = 106.4f;
	initialY = coords.y;
}

Patapon::Patapon(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	init(coords, rot, scale, layer, meshName, entityName);
}

Patapon::Patapon(Patapon const& p) : IEntity(p.localPosition, p.absoluteGlobalRot, p.localRotation, p.localScale, p.layer, p.parent, p.meshName, p.entityName, p.absoluteWidth, p.absoluteHeight)
{
	init(p.localPosition, p.absoluteGlobalRot, p.localScale, p.layer, p.meshName, p.entityName);
	velocity = p.velocity;
	if (p.getParent()) {
		this->setParent(*p.getParent().value());
	}
}

void Patapon::signal(std::string const& message) {
	if (message._Equal("die")) {
		velocity.x = 0;
		velocity.y = 400;
		dead = true;
		cheering = false;
		localRotation.x += 180;
	}
	if (message._Equal("cheer") && !cheering) {
		velocity.x = 0;
		velocity.y = 400;
		cheering = true;
	}
}

void Patapon::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight) {
	using namespace myCommon;
	for (auto& c : children) {
		(*c).onUpdate(time, deltaTime, worldWidth, worldHeight);
	}
	if (!dead) {
		if ( abs(localPosition.x + getWidth() * signAngleCos(localRotation.y)) >= worldWidth * .5f) {
			localRotation.y += 180;
			float speedFactor = (float)(std::rand() % 100) / 60.0f;
			speedFactor = speedFactor < 1 ? 1 : speedFactor;
			velocity.x = defaultVelocityX * speedFactor;
		}
	}
	localPosition.x += velocity.x * signAngleCos(localRotation.y) * deltaTime;
	localPosition.y += velocity.y * deltaTime;
	if (getPosition().y < initialY && !dead) {
		localPosition.y = initialY;
		cheering = false;
		float speedFactor = (float)(std::rand() % 100) / 60.0f;
		speedFactor = speedFactor < 1 ? 1 : speedFactor;
		velocity.x = defaultVelocityX * speedFactor;
	}
	else {
		velocity.y -= 700 * deltaTime;
	}


}
