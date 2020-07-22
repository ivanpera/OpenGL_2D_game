#pragma once
#include "PrimitiveBuilder.h"
#include "Circle.h"
class CircleBuilder : public ComponentBuilder<Circle> {
	
private:
	int numTriangles;
	float angle;
public:
	CircleBuilder();
	CircleBuilder& setVertexShader(std::string const& shaderName) override;
	CircleBuilder& setFragmentShader(std::string const& shaderName) override;
	CircleBuilder& setDrawMode(myCommon::DrawMode const& drawMode) override;
	CircleBuilder& setLPosition(myCommon::vec3 const& vec) override;
	CircleBuilder& setLRotation(myCommon::vec3 const& vec) override;
	CircleBuilder& setLScale(myCommon::vec3 const& vec) override;
	CircleBuilder& setColor(myCommon::vec4 color) override;
	CircleBuilder& setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color) override;
	CircleBuilder& setNumTriangles(int const nTriangles);
	CircleBuilder& setAngle(float const angle);
	CircleBuilder& setPointDiameter(float diameter);
	Circle build() override;
};