#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Arm.h"

class ArmBuilder : EntityBuilder<Arm> {
public:
	virtual ArmBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual ArmBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual ArmBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual ArmBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual ArmBuilder& setLayer(int const& val) override;
	virtual ArmBuilder& setMeshName(std::string const& val) override;
	virtual ArmBuilder& setTag(std::string const& val) override;
	virtual ArmBuilder& setParent(IEntity& ptr) override;
	virtual ArmBuilder& setAbsHeigth(float const& val) override;
	virtual ArmBuilder& setAbsWidth(float const& val) override;
	virtual Arm build() override;
	ArmBuilder();
};