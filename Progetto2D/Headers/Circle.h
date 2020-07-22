#pragma once
#include "common.h"
#include "Primitive.h"

class Circle : public Primitive {
private:
	unsigned nTriangles;
	float angle;
	void buildComponent() override;
	myCommon::vec4 getColor(float rad);
public:
	Circle(
		float angle,
		unsigned nTriangles,
		myCommon::vec3 coords,
		myCommon::vec3 rot,
		myCommon::vec3 scale,
		myCommon::vec4 colorTop,
		myCommon::vec4 colorRight,
		myCommon::vec4 colorBottom,
		myCommon::vec4 colorLeft,
		myCommon::DrawMode drawMode,
		std::string vertexShaderName,
		std::string fragmentShaderName,
		float pointDiameter);
};