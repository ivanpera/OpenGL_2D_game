#pragma once
#include "PrimitiveBuilder.h"
#include "Line.h"
class LineBuilder : public ComponentBuilder<Line> {
public:
	LineBuilder ();
	LineBuilder& setVertexShader(std::string const& shaderName) override;
	LineBuilder& setFragmentShader(std::string const& shaderName) override;
	LineBuilder& setDrawMode(myCommon::DrawMode const& drawMode) override;
	LineBuilder& setLPosition(myCommon::vec3 const& vec) override;
	LineBuilder& setLRotation(myCommon::vec3 const& vec) override;
	LineBuilder& setLScale(myCommon::vec3 const& vec) override;
	LineBuilder& setColor(myCommon::vec4 color) override;
	LineBuilder& setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color) override;
	LineBuilder& setPointDiameter(float diameter);
	Line build() override;
};