#include "../Headers/common.h"
#include "../Headers/Primitive.h"
#include <string>
using namespace myCommon;

Primitive::Primitive(myCommon::vec3 coords, myCommon::vec3 rot, myCommon::vec3 scale,
                       myCommon::vec4 colorTop, myCommon::vec4 colorRight, myCommon::vec4 colorBottom,
                       myCommon::vec4 colorLeft, myCommon::DrawMode drawMode, 
                       std::string vertexShaderName, std::string fragmentShaderName, 
                       float pointDiameter) 
                       : vertexShaderName(vertexShaderName),
                         fragmentShaderName(fragmentShaderName),
                         drawMode(drawMode),
                         pointDiameter(pointDiameter)
{
    this->position = { coords.x, coords.y, coords.z };
    this->rotation = { rot.x, rot.y, rot.z };
    this->scale = { scale.x, scale.y, scale.z };
    this->colorTop = { colorTop.x, colorTop.y, colorTop.z, colorTop.w };
    this->colorRight = { colorRight.x, colorRight.y, colorRight.z, colorRight.w };
    this->colorBottom = { colorBottom.x, colorBottom.y, colorBottom.z, colorBottom.w };
    this->colorLeft = { colorLeft.x, colorLeft.y, colorLeft.z, colorLeft.w };
}

void Primitive::buildComponent() {}

std::string Primitive::getVertexShaderName() const {
    return this->vertexShaderName;
}

std::string Primitive::getFragmentShaderName() const {
    return this->fragmentShaderName;
}

void Primitive::setVertexShaderName(std::string const& name)
{
    this->vertexShaderName = name;
}

void Primitive::setFragmentShaderName(std::string const& name)
{
    this->fragmentShaderName = name;
}

void Primitive::addVertex(Point const& vertex) {
    this->vertices.push_back(vertex);
}

void Primitive::addVertices(std::vector<Point> const& vertices) {
    this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
}

Primitive::Primitive()
    : vertexShaderName("vertexShader"),
    fragmentShaderName("fragmentShader"),
    drawMode(DrawMode::lines),
    pointDiameter(1)
{
    this->position = { 0, 0, 0 };
    this->rotation = { 0, 0, 0 };
    this->scale = { 1, 1, 1 };
    this->colorTop = { 1, 1, 1, 1 };
    this->colorRight = { 1, 1, 1, 1 };
    this->colorBottom = { 1, 1, 1, 1 };
    this->colorLeft = { 1, 1, 1, 1 };
}

size_t const Primitive::getNumVertices() const {
    return this->vertices.size();
}

std::vector<myCommon::Point const*> Primitive::getVertices() const
{
    using namespace myCommon;
    std::vector<Point const*> v;
    for (Point const& p : vertices)
    {
        v.push_back(&p);
    }
    return v;
}
