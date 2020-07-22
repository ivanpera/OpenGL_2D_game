#pragma once
#pragma once
#include "PrimitiveBuilder.h"
#include "Triangle.h"
class TriangleBuilder : public ComponentBuilder<Triangle> {

private:
	int numTriangles;
	float angle;
public:
	TriangleBuilder();
	TriangleBuilder& setVertexShader(std::string const& shaderName) override;
	TriangleBuilder& setFragmentShader(std::string const& shaderName) override;
	TriangleBuilder& setDrawMode(myCommon::DrawMode const& drawMode) override;
	TriangleBuilder& setLPosition(myCommon::vec3 const& vec) override;
	TriangleBuilder& setLRotation(myCommon::vec3 const& vec) override;
	TriangleBuilder& setLScale(myCommon::vec3 const& vec) override;
	TriangleBuilder& setColor(myCommon::vec4 color) override;
	TriangleBuilder& setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color) override;
	TriangleBuilder& setPointDiameter(float diameter);
	Triangle build() override;
};