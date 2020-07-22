#include "..\Headers\Quad.h"
#include "../Headers/common.h"
#include "../Headers/Primitive.h"
#include <cmath>
using namespace myCommon;

Quad::Quad(
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
	float pointDiameter) :
	Primitive(coords, rot, scale, colorTop, colorRight, colorBottom, colorLeft, drawMode, vertexShaderName, fragmentShaderName, pointDiameter)
{
	buildComponent();
}

void Quad::buildComponent() {
	addVertex({  1, -1, 0, colorBottom });
	addVertex({ -1, -1, 0, colorBottom });
	addVertex({  1,  1, 0, colorLeft });
	addVertex({ -1,  1, 0, colorLeft });
}
