#pragma once
#include "Primitive.h"
#include "common.h"

namespace BuilderUtils {
	enum class ColorRegion {
		Top, Right, Bottom, Left
	};
}

template<class T>
class ComponentBuilder {
public:
	virtual ComponentBuilder& setVertexShader(std::string const& shaderName);
	virtual ComponentBuilder& setFragmentShader(std::string const& shaderName);
	virtual ComponentBuilder& setDrawMode(myCommon::DrawMode const& drawMode);
	virtual ComponentBuilder& setLPosition(myCommon::vec3 const& vec);
	virtual ComponentBuilder& setLRotation(myCommon::vec3 const& vec);
	virtual ComponentBuilder& setLScale(myCommon::vec3 const& vec);
	virtual ComponentBuilder& setColor(myCommon::vec4 color);
	virtual ComponentBuilder& setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color);
	virtual ComponentBuilder& setPointDiameter(float diameter);
    virtual T build();
protected:
	std::string vertexShaderName, fragmentShaderName;
	myCommon::DrawMode drawMode;
	myCommon::vec3 localRotation, localPosition, localScale;
	myCommon::vec4 colorTop, colorRight, colorBottom, colorLeft;
	float pointDiameter;
    ComponentBuilder();
};