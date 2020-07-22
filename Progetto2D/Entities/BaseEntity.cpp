#include "../Headers/common.h"
#include "../Headers/IEntity.h"
#include <cmath>
#include <algorithm>
using namespace myCommon;

IEntity::IEntity(vec3 coords, vec3 rot, vec3 localRot, vec3 localScale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float absoluteWidth, float absoluteHeight) {
	this->localPosition = { coords.x, coords.y, coords.z };
	this->absoluteGlobalRot = { rot.x, rot.y, rot.z };
	this->localScale = { localScale.x, localScale.y, localScale.z };
	this->localRotation = { localRot.x, localRot.y, localRot.z };
	this->layer = layer;
	this->meshName = meshName;
	this->entityName = entityName;
	this->absoluteHeight = absoluteHeight;
	this->absoluteWidth = absoluteWidth;
	if (parent.has_value()) {
		this->parent = { *parent };
	}
	else {
		this->parent = {};
	}
}

bool IEntity::operator==(IEntity const& other)
{
	if (this == &other) {
		return true;
	}
	//you should compare other things, but eh
	return this->absoluteHeight == other.absoluteHeight &&
		this->getPosition() == other.getPosition() &&
		this->absoluteGlobalRot == other.absoluteGlobalRot &&
		this->getScale() == other.getScale() &&
		this->meshName == other.getMeshName();
}

void IEntity::onUpdate(int const time, float const deltaTime, float const worldWidth, float const worldHeight)
{

}

void IEntity::signal(std::string const& message)
{
}

std::string const& IEntity::getMeshName() const {
	return this->meshName;
}

std::string const& IEntity::getEntityName() const
{
	return this->entityName;
}

std::optional<IEntity*> IEntity::getParent() const
{
	return parent;
}

float const IEntity::getWidth() const
{
	return absoluteWidth * getScale().x;
}

float const IEntity::getHeight() const
{
	return absoluteHeight * getScale().y;
}

vec3 const IEntity::getScale() const
{
	if (parent) {
		return localScale * (*parent)->getScale();
	}
	return localScale;
}

myCommon::vec3 const IEntity::getPosition() const
{
	if (parent) {
		return localPosition + (*parent)->getPosition();
	}
	return localPosition;
}

std::vector<Primitive> const& IEntity::getComponents() const {
	return this->components;
}

std::vector<Point const*> getPVertices(IEntity const& e) {
	std::vector<Point const*> v;
	for (auto const& c : e.getChildrenEntities()) {
		std::vector<Point const*> t = getPVertices(*c);
		v.insert(v.end(), t.begin(), t.end());
	}
	for (Primitive const& c : e.getComponents()) {
		std::vector<Point const*> t = c.getVertices();
		v.insert(v.end(), t.begin(), t.end());
	}
	return v;
}

std::vector<Point> const IEntity::getGlobalMesh() const {
	std::vector<Point> mesh;
	std::vector<Point const*> v = getPVertices(*this);
	for (Point const* c : v) {
		mesh.push_back(*c);
	}
	return mesh;

}

struct Comparator
{
	bool operator() (std::shared_ptr<IEntity> const& lhs, std::shared_ptr<IEntity>const& rhs) const
	{
		return (*lhs).layer < (*rhs).layer;
	}
};

std::vector<std::shared_ptr<IEntity>> const IEntity::getChildrenEntities() const
{
	std::vector<std::shared_ptr<IEntity>> c = children;
	std::sort(c.begin(), c.end(), Comparator());
	return c;
}

myCommon::vec3 IEntity::getRotation() const
{
	if (parent) {
		return absoluteGlobalRot + (*parent)->getRotation();
	}
	return absoluteGlobalRot;
}

myCommon::vec3 IEntity::getLocalRotationR() const
{
	if (parent) {
		return localRotation + (*parent)->getLocalRotationR();
	}
	return localRotation;
}

void IEntity::setParent(IEntity& parent)
{
	this->parent = { &parent };
}

void IEntity::loadComponents() { }


