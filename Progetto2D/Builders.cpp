#include "Headers/PrimitiveBuilder.h"
#include "Headers/common.h"
#include "Headers/CircleBuilder.h"
#include "Headers/LineBuilder.h"
#include "Headers/QuadBuilder.h"
#include "Headers/TriangleBuilder.h"

#pragma region BASE_BUILDER

template<class T>
ComponentBuilder<T>::ComponentBuilder()
	: localPosition({ 0,0,0 }),
	localRotation({ 0,0,0 }),
	localScale({ 1,1,1 }),
	drawMode(myCommon::DrawMode::lines),
	pointDiameter(1),
	vertexShaderName("vertexShader"),
	fragmentShaderName("fragmentShader"),
	colorTop({1,1,1,1}),
	colorRight({ 1,1,1,1 }),
	colorBottom({ 1,1,1,1 }),
	colorLeft({ 1,1,1,1 })
{
}

template<class T>
T ComponentBuilder<T>::build()
{
	throw "Invalid call to generic builder";
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setVertexShader(std::string const& shaderName)
{
	this->vertexShaderName = shaderName;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setFragmentShader(std::string const& shaderName)
{
	this->fragmentShaderName = shaderName;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setDrawMode(myCommon::DrawMode const& drawMode)
{
	this->drawMode = drawMode;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setLPosition(myCommon::vec3 const& vec)
{
	this->localPosition = vec;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setLRotation(myCommon::vec3 const& vec)
{
	this->localRotation = vec;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setLScale(myCommon::vec3 const& vec)
{
	this->localScale = vec;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setColor(myCommon::vec4 color)
{
	this->colorTop = this->colorRight =
		this->colorBottom = this->colorLeft = color;
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color)
{
	using namespace BuilderUtils;
	switch (region)
	{
	case ColorRegion::Top:
		this->colorTop = color;
		break;
	case ColorRegion::Left:
		this->colorLeft = color;
		break;
	case ColorRegion::Bottom:
		this->colorBottom = color;
		break;
	case ColorRegion::Right:
		this->colorRight = color;
		break;
	default:
		throw "Invalid color region";
		break;
	}
	return *this;
}

template<class T>
ComponentBuilder<T>& ComponentBuilder<T>::setPointDiameter(float diameter)
{
	pointDiameter = diameter >= 0 ? diameter : pointDiameter;
	return *this;
}

#pragma endregion

#pragma region CIRCLE_BUILDER

constexpr int DEFAULT_TRIANGLES = 40;

CircleBuilder::CircleBuilder() : angle(2 * myCommon::PI), numTriangles(DEFAULT_TRIANGLES), ComponentBuilder() {
	setDrawMode(myCommon::DrawMode::triangles_fan);
}

CircleBuilder& CircleBuilder::setVertexShader(std::string const& shaderName)
{
	ComponentBuilder::setVertexShader(shaderName);
	return *this;
}

CircleBuilder& CircleBuilder::setFragmentShader(std::string const& shaderName)
{
	ComponentBuilder::setFragmentShader(shaderName);
	return *this;
}

CircleBuilder& CircleBuilder::setDrawMode(myCommon::DrawMode const& drawMode)
{
	ComponentBuilder::setDrawMode(drawMode);
	return *this;
}

CircleBuilder& CircleBuilder::setLPosition(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLPosition(vec);
	return *this;
}

CircleBuilder& CircleBuilder::setLRotation(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLRotation(vec);
	return *this;
}

CircleBuilder& CircleBuilder::setLScale(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLScale(vec);
	return *this;
}

CircleBuilder& CircleBuilder::setColor(myCommon::vec4 color)
{
	ComponentBuilder::setColor(color);
	return *this;
}

CircleBuilder& CircleBuilder::setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color)
{
	ComponentBuilder::setColorRegion(region, color);
	return *this;
}

CircleBuilder& CircleBuilder::setAngle(float angle) {
	this->angle = angle;
	return *this;
}

CircleBuilder& CircleBuilder::setNumTriangles(int nTriangles) {
	this->numTriangles = nTriangles;
	return *this;
}

Circle CircleBuilder::build() {
	return Circle(
		this->angle, this->numTriangles, this->localPosition, this->localRotation,
		this->localScale, this->colorTop, this->colorRight, this->colorBottom, this->colorLeft,
		this->drawMode, this->vertexShaderName, this->fragmentShaderName, this->pointDiameter);
}

CircleBuilder& CircleBuilder::setPointDiameter(float diameter)
{
	pointDiameter = diameter >= 0 ? diameter : pointDiameter;
	return *this;
}

#pragma endregion

#pragma region LINE_BUILDER
LineBuilder::LineBuilder() : ComponentBuilder() {
	setDrawMode(myCommon::DrawMode::lines);
}

LineBuilder& LineBuilder::setVertexShader(std::string const& shaderName)
{
	ComponentBuilder::setVertexShader(shaderName);
	return *this;
}

LineBuilder& LineBuilder::setFragmentShader(std::string const& shaderName)
{
	ComponentBuilder::setFragmentShader(shaderName);
	return *this;
}

LineBuilder& LineBuilder::setDrawMode(myCommon::DrawMode const& drawMode)
{
	ComponentBuilder::setDrawMode(drawMode);
	return *this;
}

LineBuilder& LineBuilder::setLPosition(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLPosition(vec);
	return *this;
}

LineBuilder& LineBuilder::setLRotation(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLRotation(vec);
	return *this;
}

LineBuilder& LineBuilder::setLScale(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLScale(vec);
	return *this;
}

LineBuilder& LineBuilder::setColor(myCommon::vec4 color)
{
	ComponentBuilder::setColor(color);
	return *this;
}

LineBuilder& LineBuilder::setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color)
{
	ComponentBuilder::setColorRegion(region, color);
	return *this;
}

Line LineBuilder::build() {
	return Line(
		this->localPosition, this->localRotation, this->localScale, this->colorTop, 
		this->colorRight, this->colorBottom, this->colorLeft, this->drawMode, 
		this->vertexShaderName, this->fragmentShaderName, this->pointDiameter);
}

LineBuilder& LineBuilder::setPointDiameter(float diameter)
{
	pointDiameter = diameter >= 0 ? diameter : pointDiameter;
	return *this;
}
#pragma endregion

#pragma region QUAD_BUILDER
QuadBuilder::QuadBuilder() : ComponentBuilder() {
	setDrawMode(myCommon::DrawMode::triangles_strip);
}

QuadBuilder& QuadBuilder::setVertexShader(std::string const& shaderName)
{
	ComponentBuilder::setVertexShader(shaderName);
	return *this;
}

QuadBuilder& QuadBuilder::setFragmentShader(std::string const& shaderName)
{
	ComponentBuilder::setFragmentShader(shaderName);
	return *this;
}

QuadBuilder& QuadBuilder::setDrawMode(myCommon::DrawMode const& drawMode)
{
	ComponentBuilder::setDrawMode(drawMode);
	return *this;
}

QuadBuilder& QuadBuilder::setLPosition(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLPosition(vec);
	return *this;
}

QuadBuilder& QuadBuilder::setLRotation(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLRotation(vec);
	return *this;
}

QuadBuilder& QuadBuilder::setLScale(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLScale(vec);
	return *this;
}

QuadBuilder& QuadBuilder::setColor(myCommon::vec4 color)
{
	ComponentBuilder::setColor(color);
	return *this;
}

QuadBuilder& QuadBuilder::setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color)
{
	ComponentBuilder::setColorRegion(region, color);
	return *this;
}

Quad QuadBuilder::build() {
	return Quad(
		this->localPosition, this->localRotation, this->localScale, this->colorTop,
		this->colorRight, this->colorBottom, this->colorLeft, this->drawMode,
		this->vertexShaderName, this->fragmentShaderName, this->pointDiameter);
}

QuadBuilder& QuadBuilder::setPointDiameter(float diameter)
{
	pointDiameter = diameter >= 0 ? diameter : pointDiameter;
	return *this;
}

#pragma endregion

#pragma region TRIANGLE_BUILDER
TriangleBuilder::TriangleBuilder() : ComponentBuilder() {
	setDrawMode(myCommon::DrawMode::triangles);
}

TriangleBuilder& TriangleBuilder::setVertexShader(std::string const& shaderName)
{
	ComponentBuilder::setVertexShader(shaderName);
	return *this;
}

TriangleBuilder& TriangleBuilder::setFragmentShader(std::string const& shaderName)
{
	ComponentBuilder::setFragmentShader(shaderName);
	return *this;
}

TriangleBuilder& TriangleBuilder::setDrawMode(myCommon::DrawMode const& drawMode)
{
	ComponentBuilder::setDrawMode(drawMode);
	return *this;
}

TriangleBuilder& TriangleBuilder::setLPosition(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLPosition(vec);
	return *this;
}

TriangleBuilder& TriangleBuilder::setLRotation(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLRotation(vec);
	return *this;
}

TriangleBuilder& TriangleBuilder::setLScale(myCommon::vec3 const& vec)
{
	ComponentBuilder::setLScale(vec);
	return *this;
}

TriangleBuilder& TriangleBuilder::setColor(myCommon::vec4 color)
{
	ComponentBuilder::setColor(color);
	return *this;
}

TriangleBuilder& TriangleBuilder::setColorRegion(BuilderUtils::ColorRegion region, myCommon::vec4 color)
{
	ComponentBuilder::setColorRegion(region, color);
	return *this;
}

Triangle TriangleBuilder::build() {
	return Triangle(
		this->localPosition, this->localRotation, this->localScale, this->colorTop,
		this->colorRight, this->colorBottom, this->colorLeft, this->drawMode,
		this->vertexShaderName, this->fragmentShaderName, this->pointDiameter);
}

TriangleBuilder& TriangleBuilder::setPointDiameter(float diameter)
{
	pointDiameter = diameter >= 0 ? diameter : pointDiameter;
	return *this;
}

#pragma endregion