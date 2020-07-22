#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Background.h"

class BackgroundBuilder : EntityBuilder<Background> {
public:
	virtual BackgroundBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual BackgroundBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual BackgroundBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual BackgroundBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual BackgroundBuilder& setLayer(int const& val) override;
	virtual BackgroundBuilder& setMeshName(std::string const& val) override;
	virtual BackgroundBuilder& setTag(std::string const& val) override;
	virtual BackgroundBuilder& setParent(IEntity& ptr) override;
	virtual BackgroundBuilder& setAbsHeigth(float const& val) override;
	virtual BackgroundBuilder& setAbsWidth(float const& val) override;
	virtual Background build() override;
	BackgroundBuilder();
};