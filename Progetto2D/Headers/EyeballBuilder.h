#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Eyeball.h"

class EyeballBuilder : EntityBuilder<Eyeball> {
public:
	virtual EyeballBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual EyeballBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual EyeballBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual EyeballBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual EyeballBuilder& setLayer(int const& val) override;
	virtual EyeballBuilder& setMeshName(std::string const& val) override;
	virtual EyeballBuilder& setTag(std::string const& val) override;
	virtual EyeballBuilder& setParent(IEntity& ptr) override;
	virtual EyeballBuilder& setAbsHeigth(float const& val) override;
	virtual EyeballBuilder& setAbsWidth(float const& val) override;
	virtual Eyeball build() override;
	EyeballBuilder();
};