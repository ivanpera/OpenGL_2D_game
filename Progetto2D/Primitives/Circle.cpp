#include "..\Headers\Circle.h"
#include "../Headers/common.h"
#include "../Headers/Primitive.h"
#include <cmath>
using namespace myCommon;

Circle::Circle(
	float angle,
	unsigned nTriangles,
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
	float pointDiameter) : angle(angle), nTriangles(nTriangles),
	Primitive( coords, rot, scale, colorTop, colorRight, colorBottom, colorLeft, drawMode, vertexShaderName, fragmentShaderName, pointDiameter)
{
	buildComponent();
}

float clamp(float value, float lower, float upper) {
	return value < lower ? lower : value > upper ? upper : value;
}

vec4 Circle::getColor(float rad) {
	float q = PI / 4, inv = 2 * PI - rad;
	if (rad <= q || inv <= q) {
		return colorRight;
	}
	if (rad >= q && rad <= 3 * q) {
		return colorTop;
	}
	if (rad >= 3 * q && rad <= 5 * q) {
		return colorLeft;
	}
	return colorBottom;
}

void Circle::buildComponent()
{
	float step = angle / nTriangles;
	float rad = 0;
	vec4 color = colorTop;
	switch (drawMode)
	{
	case DrawMode::triangles_fan:
		for (unsigned i = 0; i < nTriangles; i++) {
			color = getColor(rad);
			addVertex({ cos(rad), sin(rad), 0, color.x, color.y, color.z, color.w });
			rad += step;
		}
		break;
	case DrawMode::triangles_strip:
		for (unsigned i = 0; i <= nTriangles; i++) {
			color = getColor(rad);
			addVertex({ cos(rad), sin(rad), 0, color.x, color.y, color.z, color.w });
			addVertex({ cos(rad) * .8f, sin(rad) * .8f, 0, color.x, color.y, color.z, color.w });
			rad += step;
		}
		break;
	default:
		throw "Not yet supported";
	}
}

