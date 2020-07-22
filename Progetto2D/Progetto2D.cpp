#include <iostream>
#include "Headers/ShaderMaker.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <vector>
#include "Headers/ShaderKey.h"
#include "Headers/IEntity.h"
#include "Headers/Primitive.h"
#include "Headers/World.h"
#include "Headers/common.h"

glm::mat4 Projection;


typedef struct Program {
	unsigned int id;		//points to the shader
	unsigned int modelMatr; //points to the variable in the shader
	unsigned int projMatr;	//points to the variable in the shader
	unsigned int time;
	unsigned int deltaTime;
} Program;


static constexpr int GLUT_MAIN_VERSION = 4, GLUT_SUB_VERSION = 0;
static constexpr int DEFAULT_WINDOW_WIDTH = 768, DEFAULT_WINDOW_HEIGHT = 756;
static constexpr int DEFAULT_WINDOW_X = 100, DEFAULT_WINDOW_Y = 100;
static constexpr int UPDATE_PER_SECOND = 1000 / 60, PHYSICS_UPDATE_PER_SECOND = 1000 / 30;
static bool loop = true;
static void const setupGlut(int& argc, char** argv, char const* title);
static std::map<ShaderKey, Program> programs;
static std::map<std::string, unsigned int> meshes;
static Program findOrBuildShader(ShaderKey const& key);
static void loadVAO(IEntity const& entity);
static void buildShader(ShaderKey const& key);
static int parseDrawMode(myCommon::DrawMode const& drawMode);
static int timestamp = 0;
static float deltaTime = 0;
static int windowW, windowH, windowX, windowY;
static Program program = { 0,0,0 };
static std::unique_ptr<World> world;

static void initVAO(void);


void checkError(std::string op) {
	GLenum ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout << ErrorCheckValue;
		fprintf(
			stderr,
			"ERROR: %s: %s \n",
			op.c_str(),
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

int main(int argc, char** argv)
{
	using namespace glm;
	char const* title = "Titolo";
	setupGlut(argc, argv, title);
	world.reset(new World(3, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)));
	initVAO();
	std::cout << "Start\n";
	glutMainLoop();
}

glm::vec3 myCommontToGlm(myCommon::vec3 const& vec) {
	return glm::vec3(vec.x, vec.y, vec.z);
}

void drawNestedPrimitives(IEntity const& parent, size_t& vertexIdx, ShaderKey& shaderKey) {
	using namespace glm;
	vec3 centerOffset = { glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, 0 };
	for (auto const& component : parent.getComponents()) {
		ShaderKey compShaderKey = { component.getVertexShaderName(), component.getFragmentShaderName() };
		if (shaderKey != compShaderKey) {
			shaderKey = compShaderKey;
			program = findOrBuildShader(shaderKey);
			glUseProgram(program.id);
			glUniform1i(program.time, timestamp);
			glUniform1f(program.deltaTime, deltaTime);
		}
		//check if drawmode is line or point
		glLineWidth(component.pointDiameter);
		vec3 cT = myCommontToGlm(component.position);
		vec3 cS = myCommontToGlm(component.scale);
		vec3 cR = myCommontToGlm(component.rotation);
		glUniformMatrix4fv(program.projMatr, 1, GL_FALSE, value_ptr(Projection));

		mat4 Model = mat4(1.0);

		//Offset di centramento della finestra
		Model = translate(Model, centerOffset);

		//Posizionamento entità nel mondo
		Model = translate(Model, myCommontToGlm((parent.getPosition() - parent.localPosition) * parent.getScale()));

		//Rotazione entità attorno a assi globali (FINE POSIZIONAMENTO LOCALE ENTITA')
		Model = rotate(Model, radians(parent.getRotation().x), vec3(1.0, 0.0, 0.0));
		Model = rotate(Model, radians(parent.getRotation().y), vec3(0.0, 1.0, 0.0));
		Model = rotate(Model, radians(parent.getRotation().z), vec3(0.0, 0.0, 1.0));

		////Traslazione dell'entità presso punto locale
		Model = translate(Model, vec3(myCommon::signAngleCos(parent.getLocalRotationR().y), myCommon::signAngleCos(parent.getLocalRotationR().x), 1) * myCommontToGlm(parent.localPosition * parent.getScale()));

		//Rotazione entità attorno a propri assi
		Model = rotate(Model, radians(parent.getLocalRotationR().x), vec3(1.0, 0.0, 0.0));
		Model = rotate(Model, radians(parent.getLocalRotationR().y), vec3(0.0, 1.0, 0.0));
		Model = rotate(Model, radians(parent.getLocalRotationR().z), vec3(0.0, 0.0, 1.0));

		////traslazione nella corretta posizione della primitiva (FINE ASSEMBLAMENTO ENTITA')
		Model = translate(Model, cT * vec3(parent.getWidth(), parent.getHeight(), 1) * cS);

		////rotazione attorno a origine della primitiva
		Model = rotate(Model, radians(cR.x), vec3(1.0, 0.0, 0.0));
		Model = rotate(Model, radians(cR.y), vec3(0.0, 1.0, 0.0));
		Model = rotate(Model, radians(cR.z), vec3(0.0, 0.0, 1.0));

		Model = scale(Model, vec3(parent.getWidth(), parent.getHeight(), 1) * cS);
		
		glUniformMatrix4fv(program.modelMatr, 1, GL_FALSE, value_ptr(Model));
		glDrawArrays(parseDrawMode(component.drawMode), vertexIdx, component.getNumVertices());
		vertexIdx += component.getNumVertices();
	}
}

void drawPrimitives(IEntity const& parent, size_t& vertexIdx, ShaderKey& shaderKey) {
	drawNestedPrimitives(parent, vertexIdx, shaderKey);
}

void drawChildrenR(IEntity const& parent, size_t& vertexIdx, ShaderKey& shaderKey) {
	using namespace glm;
	for (auto const& child : parent.getChildrenEntities()) {
		drawChildrenR(*child, vertexIdx, shaderKey);
		drawNestedPrimitives(*child, vertexIdx, shaderKey);
	}
}

void onDisplay(void) {
	using namespace glm;

	glClearColor(0.0f, 0.4f, 0.5f, .1f);
	
	ShaderKey shaderKey = {"", ""};
	std::string vaoKey = "";
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto const& entityPair : (*world).getEntities()) {
		size_t vertexIdx = 0;
		auto const& entity = *entityPair.second;
		std::string entityVAO = entity.getMeshName();
		if (vaoKey != entityVAO) {
			glBindVertexArray(0);
			vaoKey = entityVAO;
			if (meshes.count(vaoKey) == 0) {
				loadVAO(entity);
			}
			glBindVertexArray(meshes.at(vaoKey));
		}

		drawChildrenR(entity, vertexIdx, shaderKey);
		drawPrimitives(entity, vertexIdx, shaderKey);
		
	}
	glBindVertexArray(0);
	glutSwapBuffers();
	checkError("draw");
	
}


void loadVAO(IEntity const& entity) {

	std::cout << "meshname: " << entity.getMeshName() << "\n";
	std::string meshKey = entity.getMeshName();
	if (meshes.count(meshKey) == 0) {
		meshes.insert({ meshKey, 0 });
		unsigned int& VAO = meshes.at(meshKey);
		std::vector<myCommon::Point> const& mesh = entity.getGlobalMesh();
		unsigned int VBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(myCommon::Point), mesh.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
		checkError("Mesh loading");
	}
}

void initVAO(void) {
	ShaderKey last = { "", "" };
	for (auto const& entPair : (*world).getEntities()) {
		IEntity const& entity = *entPair.second;

		loadVAO(entity);
		
		for (auto const& component : entity.getComponents()) {
			ShaderKey current = { component.getVertexShaderName(), component.getFragmentShaderName() };
			if (current != last) {
				findOrBuildShader(current);
				last = current;
			}
			checkError("Shader building");
		}
	}
	
	std::cout << "initVAO ok\n";
	std::cout << "MeshCount: " << meshes.size() << "\n";
}

void onKeyDown(unsigned char k, int x, int y) {
	// octal equivalent of the Escape key
	if (k == 033) {
		glutLeaveMainLoop();
	}
	else {
		(*world).onKeyDown(k);
	}
}

void onSpecial(int k, int x, int y) {
	switch (k)
	{
	case GLUT_KEY_UP:
		(*world).onKeyDown('u');
		break;
	case GLUT_KEY_RIGHT:
		(*world).onKeyDown('r');
		break;
	case GLUT_KEY_DOWN:
		(*world).onKeyDown('d');
		break;
	case GLUT_KEY_LEFT:
		(*world).onKeyDown('l');
		break;
	default:
		break;
	}
}

void onResize(int w, int h) {

	int offX = (w - windowW)/2, offY = (h - windowH)/2;
	glViewport(offX, offY, windowW, windowH);
	Projection = glm::ortho(0.0f, float(windowW), 0.0f, float(windowH));
	glutReshapeWindow(windowW, windowH);
	glutPostRedisplay();
}

void physicsUpdate(int v) {
	int oldTime = timestamp;
	timestamp = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = glm::clamp((float)((timestamp - oldTime)) / 1000, 0.0f, (1.0f * PHYSICS_UPDATE_PER_SECOND) / 1000);
	(*world).update(timestamp, deltaTime);

	glutPostRedisplay();
	glutTimerFunc(PHYSICS_UPDATE_PER_SECOND, physicsUpdate, 0);
}

void const setupGlut(int& argc, char** argv, char const* title) {
	using namespace glm;
	glutInit(&argc, argv);
	glutInitContextVersion(GLUT_MAIN_VERSION, GLUT_SUB_VERSION);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int const screenW = glutGet(GLUT_SCREEN_WIDTH), screenH = glutGet(GLUT_SCREEN_HEIGHT);
	int const percentageW = 40, percentageH = 70;
	
	if (screenW <= 0 && screenH <= 0) {
		windowW = DEFAULT_WINDOW_WIDTH;
		windowH = DEFAULT_WINDOW_HEIGHT;
		windowX = DEFAULT_WINDOW_X;
		windowY = DEFAULT_WINDOW_Y;
	} else {
		windowW = screenW * percentageW / 100;
		windowH = screenH * percentageH / 100;
		windowX = screenW / 2 - windowW / 2;
		windowY = screenH / 2 - windowH / 2;
	}

	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(windowX, windowY);
	glutCreateWindow(title);
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onResize);
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecial);
	glutTimerFunc(PHYSICS_UPDATE_PER_SECOND, physicsUpdate, 0);
	glewExperimental = GL_TRUE; //?
	glewInit();					//?
	Projection = glm::ortho(0.0f, float(windowW), 0.0f, float(windowH));
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Might experiment?
	checkError("SetupGlut");
	glClearColor(0.0f, 0.4f, 0.5f, .1f);
	std::cout << "SetupGlut ok\n";
}


Program findOrBuildShader(ShaderKey const& key) {
	if (programs.count(key) <= 0) {
		buildShader(key);
	}
	return programs.at(key);
}

int parseDrawMode(myCommon::DrawMode const& drawMode) {
	using namespace myCommon;
	switch (drawMode)
	{
	case DrawMode::lines:
		return GL_LINES;
	case DrawMode::lines_strip:
		return GL_LINE_STRIP;
	case DrawMode::lines_loop:
		return GL_LINE_LOOP;
	case DrawMode::points:
		return GL_POINTS;
	case DrawMode::triangles:
		return GL_TRIANGLES;
	case DrawMode::triangles_fan:
		return GL_TRIANGLE_FAN;
	case DrawMode::triangles_strip:
		return GL_TRIANGLE_STRIP;
	default:
		throw "Unrecognized draw mode";
	}
}

void buildShader(ShaderKey const& key) {
	Program program;
	program.id = ShaderMaker::createProgram(key.vertShader.c_str(), key.fragShader.c_str());
	program.projMatr = glGetUniformLocation(program.id, "Projection");
	program.modelMatr = glGetUniformLocation(program.id, "Model");
	program.time = glGetUniformLocation(program.id, "t");
	program.deltaTime = glGetUniformLocation(program.id, "dt");
	programs.insert({ key, program });
}