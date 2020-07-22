#ifndef PRIMITIVE_SHAPE
#define PRIMITIVE_SHAPE

#include "common.h"
#include <vector>
#include <string>
class Primitive {
private:
	virtual void buildComponent();
	
public:
	size_t const getNumVertices() const;
	std::vector<myCommon::Point const*> getVertices() const;
	myCommon::DrawMode drawMode;
	myCommon::vec3 rotation, position, scale, globalRotation, globalPosition, globalScale;
	myCommon::vec4 colorTop, colorRight, colorBottom, colorLeft;
	float pointDiameter;
	std::string getVertexShaderName() const;
	std::string getFragmentShaderName() const;
	void setVertexShaderName(std::string const& name);
	void setFragmentShaderName(std::string const& name);
	~Primitive() {};

protected:
	std::vector<myCommon::Point> vertices;
	std::string vertexShaderName, fragmentShaderName;
	void addVertex(myCommon::Point const& vertex);
	void addVertices(std::vector<myCommon::Point> const& vertices);
	Primitive();
	Primitive(
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
#endif