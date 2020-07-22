#pragma once
#include "IEntity.h"
#include "common.h"
#include "EntityBuilder.h"
#include "Key.h"

class KeyBuilder : EntityBuilder<Key> {
public:
	virtual KeyBuilder& setLocalRotation(myCommon::vec3 const& vec) override;
	virtual KeyBuilder& setRotation(myCommon::vec3 const& vec) override;
	virtual KeyBuilder& setPostion(myCommon::vec3 const& vec) override;
	virtual KeyBuilder& setScale(myCommon::vec3 const& vec) override;
	virtual KeyBuilder& setLayer(int const& val) override;
	virtual KeyBuilder& setMeshName(std::string const& val) override;
	virtual KeyBuilder& setTag(std::string const& val) override;
	virtual KeyBuilder& setParent(IEntity& ptr) override;
	virtual KeyBuilder& setAbsHeigth(float const& val) override;
	virtual KeyBuilder& setAbsWidth(float const& val) override;
	virtual Key build() override;
	KeyBuilder();
};