#pragma once
#include "IEntity.h"
#include "common.h"

template<class T>
class EntityBuilder {
private:
	
public:
	virtual EntityBuilder& setLocalRotation(myCommon::vec3 const& vec);
	virtual EntityBuilder& setRotation(myCommon::vec3 const& vec);
	virtual EntityBuilder& setPostion(myCommon::vec3 const& vec);
	virtual EntityBuilder& setScale(myCommon::vec3 const& vec);
	virtual EntityBuilder& setAbsWidth(float const& val);
	virtual EntityBuilder& setAbsHeigth(float const& val);
	virtual EntityBuilder& setLayer(int const& val);
	virtual EntityBuilder& setMeshName(std::string const& val);
	virtual EntityBuilder& setTag(std::string const& val);
	virtual EntityBuilder& setParent(IEntity& ptr);
	virtual T build();
protected:
	EntityBuilder();
	myCommon::vec3 localRot, rot, pos, scale;
	float width, height;
	int layer;
	std::string tag, meshName;
	std::optional<IEntity*> parent;
};