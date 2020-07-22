

#include "../Headers/ActivationBox.h"
#include "../Headers/QuadBuilder.h"

void ActivationBox::loadComponents()
{
	//key box
	Quad q = QuadBuilder()
		.setLScale({ 1.0f, 1.0f, 1 })
		.setColor({ .0f, 1, 0.0f, 1 })
		.build();
	components.push_back(q);

	//key box inner
	q = QuadBuilder()
		.setLScale({ .8f, 0.8f, 1 })
		.setColor({ .0f, 0.2f, 0.86f, 1 })
		.build();
	components.push_back(q);
}

ActivationBox::ActivationBox(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	loadComponents();
	this->absoluteHeight = 56.7f;
	this->absoluteWidth = 57.6f;
}

