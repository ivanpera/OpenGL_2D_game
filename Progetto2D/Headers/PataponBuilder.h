#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Patapon.h"

class PataponBuilder : EntityBuilder<Patapon> {
private:
	float speedFactor = 1.0f;
public:
	virtual PataponBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual PataponBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual PataponBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual PataponBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual PataponBuilder& setLayer(int const& val) override;
	virtual PataponBuilder& setMeshName(std::string const& val) override;
	virtual PataponBuilder& setTag(std::string const& val) override;
	virtual PataponBuilder& setParent(IEntity& ptr) override;
	virtual PataponBuilder& setAbsHeigth(float const& val) override;
	virtual PataponBuilder& setAbsWidth(float const& val) override;
	virtual Patapon build() override;
	PataponBuilder();
};