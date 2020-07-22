#include "Headers/common.h"
#include "Headers/EntityBuilder.h"
#include "Headers/ABoxBuilder.h"
#include "Headers/ArmBuilder.h"
#include "Headers/BgBuilder.h"
#include "Headers/EyeballBuilder.h"
#include "Headers/HatBuilder.h"
#include "Headers/KeyBuilder.h"
#include "Headers/LegBuilder.h"
#include "Headers/PataponBuilder.h"

#pragma region BASE_BUILDER

template<class T>
EntityBuilder<T>::EntityBuilder() 
	: localRot({ 0,0,0 }), 
	rot({ 0,0,0 }),
	pos({ 0,0,0 }),
	scale({ 1,1,1 }),
	layer(0),
	tag(""),
	meshName("default"),
	parent(std::optional<IEntity*>{}),
	width(1),
	height(1)
{

}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setLocalRotation(myCommon::vec3 const& vec) {
	this->localRot = vec;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setRotation(myCommon::vec3 const& vec) {
	this->rot = vec;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setPostion(myCommon::vec3 const& vec) {
	this->pos = vec;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setScale(myCommon::vec3 const& vec) {
	this->scale = vec;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setAbsWidth(float const& val)
{
	this->width = val;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setAbsHeigth(float const& val)
{
	this->height = val;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setLayer(int const& val) {
	this->layer = val;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setMeshName(std::string const& val) {
	this->meshName = val;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setTag(std::string const& val) {
	this->tag = val;
	return *this;
}

template<class T>
EntityBuilder<T>& EntityBuilder<T>::setParent(IEntity& ptr) {
	this->parent = { &ptr };
	return *this;
}

template<class T>
T EntityBuilder<T>::build() {
	throw "Invalid call to generic builder";
}

#pragma endregion

#pragma region ABOX_BUILDER

ABoxBuilder::ABoxBuilder() : EntityBuilder()
{
	
}

ABoxBuilder& ABoxBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


ABoxBuilder& ABoxBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

ABoxBuilder& ABoxBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

ABoxBuilder& ABoxBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

ABoxBuilder& ABoxBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

ABoxBuilder& ABoxBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

ABoxBuilder& ABoxBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

ABoxBuilder& ABoxBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

ABoxBuilder& ABoxBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

ABoxBuilder& ABoxBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

ActivationBox ABoxBuilder::build() {
	return ActivationBox(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}
#pragma endregion

#pragma region ARM_BUILDER
ArmBuilder::ArmBuilder() : EntityBuilder()
{

}

ArmBuilder& ArmBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


ArmBuilder& ArmBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

ArmBuilder& ArmBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

ArmBuilder& ArmBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

ArmBuilder& ArmBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

ArmBuilder& ArmBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

ArmBuilder& ArmBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

ArmBuilder& ArmBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

ArmBuilder& ArmBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

ArmBuilder& ArmBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

Arm ArmBuilder::build() {
	return Arm(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}
#pragma endregion

#pragma region BG_BUILDER
BackgroundBuilder::BackgroundBuilder() : EntityBuilder()
{
	this->tag = "Background";
}

BackgroundBuilder& BackgroundBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


BackgroundBuilder& BackgroundBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

Background BackgroundBuilder::build() {
	return Background(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}

BackgroundBuilder& BackgroundBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

BackgroundBuilder& BackgroundBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

#pragma endregion

#pragma region EYEBALL_BUILDER
EyeballBuilder::EyeballBuilder() : EntityBuilder()
{

}

EyeballBuilder& EyeballBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


EyeballBuilder& EyeballBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

EyeballBuilder& EyeballBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

EyeballBuilder& EyeballBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

EyeballBuilder& EyeballBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

EyeballBuilder& EyeballBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

EyeballBuilder& EyeballBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

EyeballBuilder& EyeballBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

Eyeball EyeballBuilder::build() {
	return Eyeball(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}

EyeballBuilder& EyeballBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

EyeballBuilder& EyeballBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

#pragma endregion

#pragma region HAT_BUILDER
HatBuilder::HatBuilder() : EntityBuilder()
{

}

HatBuilder& HatBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


HatBuilder& HatBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

HatBuilder& HatBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

HatBuilder& HatBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

HatBuilder& HatBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

HatBuilder& HatBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

HatBuilder& HatBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

HatBuilder& HatBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

HatBuilder& HatBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

HatBuilder& HatBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

Hat HatBuilder::build() {
	return Hat(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}
#pragma endregion

#pragma region KEY_BUILDER
KeyBuilder::KeyBuilder() : EntityBuilder()
{

}

KeyBuilder& KeyBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


KeyBuilder& KeyBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

KeyBuilder& KeyBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

KeyBuilder& KeyBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

KeyBuilder& KeyBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

KeyBuilder& KeyBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

KeyBuilder& KeyBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

KeyBuilder& KeyBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

KeyBuilder& KeyBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

KeyBuilder& KeyBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

Key KeyBuilder::build() {
	return Key(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}
#pragma endregion

#pragma region LEG_BUILDER
LegBuilder::LegBuilder() : EntityBuilder()
{

}

LegBuilder& LegBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


LegBuilder& LegBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

LegBuilder& LegBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

LegBuilder& LegBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

LegBuilder& LegBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

LegBuilder& LegBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

LegBuilder& LegBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

LegBuilder& LegBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

LegBuilder& LegBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

LegBuilder& LegBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

Leg LegBuilder::build() {
	return Leg(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}
#pragma endregion

#pragma region PATAPON_BUILDER
PataponBuilder::PataponBuilder() : EntityBuilder()
{

}

PataponBuilder& PataponBuilder::setLocalRotation(myCommon::vec3 const& vec)
{
	EntityBuilder::setLocalRotation(vec);
	return *this;
}


PataponBuilder& PataponBuilder::setRotation(myCommon::vec3 const& vec) {
	EntityBuilder::setRotation(vec);
	return *this;
}

PataponBuilder& PataponBuilder::setPostion(myCommon::vec3 const& vec) {
	EntityBuilder::setPostion(vec);
	return *this;
}

PataponBuilder& PataponBuilder::setScale(myCommon::vec3 const& vec) {
	EntityBuilder::setScale(vec);
	return *this;
}

PataponBuilder& PataponBuilder::setLayer(int const& val) {
	EntityBuilder::setLayer(val);
	return *this;
}

PataponBuilder& PataponBuilder::setMeshName(std::string const& val) {
	EntityBuilder::setMeshName(val);
	return *this;
}

PataponBuilder& PataponBuilder::setTag(std::string const& val) {
	EntityBuilder::setTag(val);
	return *this;
}

PataponBuilder& PataponBuilder::setParent(IEntity& ptr) {
	EntityBuilder::setParent(ptr);
	return *this;
}

PataponBuilder& PataponBuilder::setAbsHeigth(float const& val)
{
	EntityBuilder::setAbsHeigth(val);
	return *this;
}

PataponBuilder& PataponBuilder::setAbsWidth(float const& val)
{
	EntityBuilder::setAbsWidth(val);
	return *this;
}

Patapon PataponBuilder::build() {
	return Patapon(this->pos, this->rot, this->localRot, this->scale, this->layer, this->parent, this->meshName, this->tag, this->width, this->height);
}
#pragma endregion

