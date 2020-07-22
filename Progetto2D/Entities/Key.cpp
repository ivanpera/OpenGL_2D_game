#include "../Headers/Key.h"
#include "../Headers/QuadBuilder.h"
#include "../Headers/TriangleBuilder.h"

void Key::init(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 scale, int layer, std::string meshName, std::string entityName) {
	absoluteWidth = 40.0f;
	absoluteHeight = 40.0f;
	loadComponents();
}

Key::Key(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	init(coords, rot, scale, layer, meshName, entityName);
}

Key::Key(Key const& p) : IEntity(p.localPosition, p.absoluteGlobalRot, p.localRotation, p.localScale, p.layer, p.parent, p.meshName, p.entityName, p.absoluteWidth, p.absoluteHeight)
{
	init(p.localPosition, p.absoluteGlobalRot, p.localScale, p.layer, p.meshName, p.entityName);
}

void Key::loadComponents()
{
	//outer
	Quad q = QuadBuilder()
		.setColor({ 0.5f, 0.0f, 0.5f, 1 })
		.build();
	components.push_back(q);
	//inner
	q = QuadBuilder()
		.setLScale({ .75f, .75f, 1 })
		.setColor({ 0.5f, 0.5f, 0.5f, 1 })
		.build();
	components.push_back(q);

	Triangle t = TriangleBuilder()
		.setLScale({ 0.375, 0.375, 1 })
		.setLPosition({0, 0, 0})
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(t);

	q = QuadBuilder()
		.setLScale({ .1f,.3f,1 })
		.setLPosition({0,-0.5f,0})
		.setColor({ 0,0,0,1 })
		.build();
	components.push_back(q);

}

void Key::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight) {
	using namespace myCommon;
	if (dissolve) {
		for (auto& c : components) {
			localRotation.z -= 1;
			
			vec3 nextScale = localScale + scaleFactor * deltaTime;
			localScale = nextScale >= 2.5f ? vec3({ 2.5f,2.5f,2.5f }) : nextScale <= 0.25f ? vec3({ 0.25f,0.25f,0.25f }) : nextScale;
		}
	}
	localPosition += velocity * deltaTime;
}

void Key::signal(std::string const& message)
{
	if (message._Equal("ok") && !dissolve) {
		for (auto& c : components) {
			c.setFragmentShaderName("fragDissolve");
		}
		components.at(1).setFragmentShaderName("fragDissolveOk");
		velocity = { velocity.x/2,150,0 };
		dissolve = true;
		scaleFactor = 0.075f;
	}
	else if (message._Equal("ko") && !dissolve) {
		for (auto& c : components) {
			c.setFragmentShaderName("fragDissolve");
		}
		components.at(1).setFragmentShaderName("fragDissolveKo");
		velocity = { velocity.x / 2, -250,0 };
		dissolve = true;
		scaleFactor = -0.075f;
	}
	else if (message._Equal("lit") && !dissolve) {
		components.at(0).setFragmentShaderName("fragmentLit");
	}
}

