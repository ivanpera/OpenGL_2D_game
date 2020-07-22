#ifndef IENTITY
#define IENTITY

#include "common.h"
#include "Primitive.h"
#include <string>
#include <vector>
#include <memory>
#include <optional>

class IEntity {
private:
	virtual void loadComponents();
	IEntity();
public:
	bool operator == (IEntity const& other);
	~IEntity() {};
	virtual void onUpdate(int const time, float const deltatime, float const worldWidth, float const WorldHeight);
	virtual void signal(std::string const& message);
	std::string const& getMeshName() const;
	std::string const& getEntityName() const;
	void setParent(IEntity& parent);
	std::optional<IEntity*> getParent() const;
	float const getWidth() const;
	float const getHeight() const;
	myCommon::vec3 const getScale() const;
	myCommon::vec3 const getPosition() const;
	std::vector<Primitive> const& getComponents() const;
	std::vector<myCommon::Point> const getGlobalMesh() const;
	std::vector<std::shared_ptr<IEntity>> const getChildrenEntities() const;
	myCommon::vec3 getRotation() const;
	myCommon::vec3 getLocalRotationR() const;
	myCommon::vec3 localPosition, localRotation, localScale, absoluteGlobalRot;
	int layer;
protected:
	std::optional<IEntity*> parent;
	float absoluteWidth, absoluteHeight;
	std::string meshName, entityName;
	std::vector<std::shared_ptr<IEntity>> children;
	std::vector<Primitive> components;
	IEntity(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 localRot, myCommon::vec3 scale, int layer, std::optional<IEntity*> parent, std::string meshName, std::string entityName, float const absoluteWidth, float const absoluteHeigth);
	template <class T>
	void loadEntity(T entity) {
		this->children.push_back(std::shared_ptr<T>(new T(entity)));
	}
	
};

#endif