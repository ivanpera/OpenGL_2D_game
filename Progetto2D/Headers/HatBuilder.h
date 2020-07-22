#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Hat.h"

class HatBuilder : EntityBuilder<Hat> {
public:
	virtual HatBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual HatBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual HatBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual HatBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual HatBuilder& setLayer(int const& val) override;
	virtual HatBuilder& setMeshName(std::string const& val) override;
	virtual HatBuilder& setTag(std::string const& val) override;
	virtual HatBuilder& setParent(IEntity& ptr) override;
	virtual HatBuilder& setAbsHeigth(float const& val) override;
	virtual HatBuilder& setAbsWidth(float const& val) override;
	virtual Hat build() override;
	HatBuilder();
};