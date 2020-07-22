#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Leg.h"

class LegBuilder : EntityBuilder<Leg> {
public:
	virtual LegBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual LegBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual LegBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual LegBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual LegBuilder& setLayer(int const& val) override;
	virtual LegBuilder& setMeshName(std::string const& val) override;
	virtual LegBuilder& setTag(std::string const& val) override;
	virtual LegBuilder& setParent(IEntity& ptr) override;
	virtual LegBuilder& setAbsHeigth(float const& val) override;
	virtual LegBuilder& setAbsWidth(float const& val) override;
	virtual Leg build() override;
	LegBuilder();
};