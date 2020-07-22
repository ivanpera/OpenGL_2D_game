#include "../Headers/Primitive.h"
#include "../Headers/common.h"
#include "../Headers/Triangle.h"

#include <string>

using namespace myCommon;

Triangle::Triangle(
	vec3 coords,
	vec3 rot,
	vec3 scale,
	vec4 colorTop,
	vec4 colorRight,
	vec4 colorBottom,
	vec4 colorLeft,
	DrawMode drawMode,
	std::string vertexShaderName,
	std::string fragmentShaderName,
	float pointDiameter) : Primitive(coords, rot, scale, colorTop, colorRight, colorBottom, colorLeft, drawMode, vertexShaderName, fragmentShaderName, pointDiameter)
{
    buildComponent();
}

void Triangle::buildComponent() {
    addVertex({  1, 0, 0, colorLeft });
    addVertex({  0, 1, 0, colorTop });
    addVertex({ -1, 0, 0, colorRight });
}