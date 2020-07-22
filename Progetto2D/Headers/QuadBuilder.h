#pragma once
#include "PrimitiveBuilder.h"
#include "Quad.h"
class QuadBuilder : public ComponentBuilder<Quad> {

private:
	int numTriangles;
	float angle;
public:
	QuadBuilder();
	QuadBuilder& setVertexShader(std::string const& shaderName) override;
	QuadBuilder& setFragmentShader(std::string const& shaderName) override;
	QuadBuilder& setDrawMode(myCommon::DrawMode const& drawMode) override;
	QuadBuilder& setLPosition(myCommon::vec3 const& vec) override;
	QuadBuilder& setLRotation(myCommon::vec3 const& vec) override;
	QuadBuilder& setLScale(myCommon::vec3 const& vec) override;
	QuadBuilder& setColor(myCommon::vec4 color) override;
	QuadBuilder& setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color) override;
	QuadBuilder& setNumTriangles(int const nTriangles);
	QuadBuilder& setAngle(float const angle);
	QuadBuilder& setPointDiameter(float diameter);
	Quad build() override;
};