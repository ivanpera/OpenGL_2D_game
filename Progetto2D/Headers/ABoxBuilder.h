#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "ActivationBox.h"

class ABoxBuilder : EntityBuilder<ActivationBox>{
public:
	virtual ABoxBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual ABoxBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual ABoxBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual ABoxBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual ABoxBuilder& setLayer(int const& val) override;
	virtual ABoxBuilder& setMeshName(std::string const& val) override;
	virtual ABoxBuilder& setTag(std::string const& val) override;
	virtual ABoxBuilder& setParent(IEntity& ptr) override;
	virtual ABoxBuilder& setAbsHeigth(float const& val) override;
	virtual ABoxBuilder& setAbsWidth(float const& val) override;
	virtual ActivationBox build() override;
	ABoxBuilder();
};