#include "../Headers/Background.h"
#include "../Headers/QuadBuilder.h"
#include "../Headers/CircleBuilder.h"
void Background::loadComponents()
{
	//sky
	Quad q = QuadBuilder()
		.setColor({ 0.909f, 0.494f, 0.015f, 1 })
		.setLScale({1, .25f, 1})
		.setLPosition({ 0, 1, 0 })
		.setColorRegion(BuilderUtils::ColorRegion::Bottom, { 0.992f, 0.890f, 0.654f, 1})
		.build();
	components.push_back(q);
	//ground
	 q = QuadBuilder()
		.setColor({ 0.247059f, 0.4470588f, 0.4980392f, 1 })
		.setLScale({1, .05f, 1})
		.setLPosition( {0, -1, 0})
		.build();
	components.push_back(q);
	//ground inner
	q = QuadBuilder()
		.setLScale({ 1, .24f, 1 })
		.setColor({ 0.0f, 0.4f, 0.5f, 1 })
		.setLPosition({ 0, -getHeight() / 2, 0 })
		.build();
	components.push_back(q);

}

Background::Background(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight)
	: IEntity(coords, rot, localRot, scale, layer, parent, meshName, entityName, absoluteWidth, absoluteHeight)
{
	loadComponents();
}

