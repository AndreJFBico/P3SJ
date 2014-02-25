#include "Manager.h"

void Manager::initManager()
{
	Objs = new std::unordered_map<int, Drawable*>;
	camera = new Camera();
	manipulator = new Manipulator();
	lightAttrs = Default;
}

void Manager::initScene()
{
	camera->setPerspective(tFOVY, WINDOW_WIDTH / WINDOW_HEIGHT, tNEAR, tFAR);
	camera->setCenter(glm::vec3(0.0, 0.0, -24.0f));
	camera->updateCamera();
	ShaderProgram* sh = createShaderProgram("..\\shaders\\vertex_shader.glsl", "..\\shaders\\fragment_shader.glsl");

	Texture* tex = new Texture2D();
	PieceReader::getInstance().readObject("..\\objects\\teapot.obj");
	tex->load("..\\textures\\stone.tga");
	Piece *p = new Piece(PieceReader::getInstance().getVertices(), PieceReader::getInstance().getIndices(), sh, tex, 0);	
	std::pair<int, Piece*> val(p->getID(), p);
	Objs->insert(val);
	PieceReader::getInstance().clearAll();

	addGrid(-0.5, 0.0, 0.0, 1.0f);
}

void Manager::draw()
{
	updateLightAttrs();
	updateRotation();
	for (std::unordered_map<int, Drawable*>::iterator it = Objs->begin(); it != Objs->end(); ++it)
	{
		it->second->draw(camera->getViewMatrix(), camera->getProjectionMatrix(), camera->computeCameraCenter());
	}
}

void Manager::updateCameraRotation(float x, float y)
{
	camera->setRotationAngleY(camera->getRotationAngleY() + (x - camera->getLast_mx()));
	camera->setRotationAngleX(camera->getRotationAngleX() + (y - camera->getLast_my()));
	camera->setLast_mx(x);
	camera->setLast_my(y);
	camera->updateCamera();
}

void Manager::updateCameraPosition(float x, float y)
{
	camera->setCenter(glm::vec3(camera->getCenter().x + ((x - camera->getLast_mx()) / -camera->getCenter().z), camera->getCenter().y + ((y - camera->getLast_my()) / -camera->getCenter().z), camera->getCenter().z));
}

void Manager::updateCameraZoom(int amount)
{
	if (amount > 0)
		camera->setCenter(glm::vec3(camera->getCenter().x, camera->getCenter().y, camera->getCenter().z + 1));
	else camera->setCenter(glm::vec3(camera->getCenter().x, camera->getCenter().y, camera->getCenter().z - 1));
}

void Manager::updateLastMXY(float x, float y)
{
	camera->setLast_mx(x);
	camera->setLast_my(y);
	camera->updateCamera();
}

Piece* Manager::getPiece(int ID)
{
	return (Piece*)Objs->find(ID)->second;
}


void Manager::setRotType(int rottype)
{
	if (rotation == rottype)
		rotation = NONE;
	else
		rotation = rottype;
}

void Manager::addGrid(float x, float y, float z, float size)
{
	ShaderProgram* sh = createShaderProgram("..\\shaders\\vertex_shader.glsl", "..\\shaders\\fragment_shader.glsl");
	Vertex v;
	std::vector<Vertex> *vertexes = new std::vector<Vertex>;
	std::vector<unsigned int> *indexes = new std::vector<unsigned int>;
	int HALF_GRID_SIZE = 5;

	for (int i = -HALF_GRID_SIZE; i <= HALF_GRID_SIZE; i++)
	{
		v.XYZW = glm::vec4((float)i, 0, (float)-HALF_GRID_SIZE, 1.0f), v.RGBA = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		v.NORMAL = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes->push_back(v);
		v.XYZW = glm::vec4((float)i, 0, (float)HALF_GRID_SIZE, 1.0f), v.RGBA = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		v.NORMAL = glm::vec4(0.0f, 1.0, 0.0f, 1.0f);
		vertexes->push_back(v);
		v.XYZW = glm::vec4((float)-HALF_GRID_SIZE, 0, (float)i, 1.0f), v.RGBA = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		v.NORMAL = glm::vec4(0.0f, 1.0, 0.0f, 1.0f);
		vertexes->push_back(v);
		v.XYZW = glm::vec4((float)HALF_GRID_SIZE, 0, (float)i, 1.0f), v.RGBA = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		v.NORMAL = glm::vec4(0.0f, 1.0, 0.0f, 1.0f);
		vertexes->push_back(v);
	}

	for (int i = 0; i < vertexes->size(); i++)
	{
		indexes->push_back(i);
	}

	Piece *p = new Piece(*vertexes, *indexes, sh, 2);
	std::pair<int, Piece*> val(p->getID(), p);
	Objs->insert(val);
	p->drawWithLines();
	p->transformCenter(glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0, 0.0))));
	p->transformCenter(glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, y, 0.0))));
	p->transformCenter(glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, z))));
}

void Manager::incLightAttr()
{
	if (lightAttrs == Default)
		lightAttrs = Ruby;
	else if (lightAttrs == Ruby)
		lightAttrs = Gold;
	else if (lightAttrs == Gold)
		lightAttrs = Silver;
	else if (lightAttrs == Silver)
		lightAttrs = Esmerald;
	else if (lightAttrs == Esmerald)
		lightAttrs = Cyan;
	else if (lightAttrs == Cyan)
		lightAttrs = Default;
}

void Manager::updateLightAttrs()
{
	switch (lightAttrs)
	{
	case Default:
		((Piece*)Objs->find(0)->second)->setLigthAttrs(
			glm::vec3(0.0, 0.0, 27.0),
			glm::vec2(0.0f, 0.0005f),
			glm::vec3(0.3f, 0.3f, 0.3f),
			glm::vec3(0.9f, 0.9f, 0.9f),
			glm::vec3(0.9f, 0.9f, 0.9f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(0.9f, 0.9f, 0.9f),
			glm::vec3(0.9f, 0.9f, 0.9f),
			64.0f);
		break;
	case Ruby:
		((Piece*)Objs->find(0)->second)->setLigthAttrs(	
			glm::vec3(0.0, 0.0, 27.0),//pos 
			glm::vec2(0.0f, 0.0005f),//attenuation
			glm::vec3(0.1745, 0.01175, 0.01175),// AmbientLightColor
			glm::vec3(0.61424, 0.04136, 0.04136),// LightDiffuseColor
			glm::vec3(0.727811, 0.626959, 0.626959),// LightSpecularColor
			glm::vec3(0.8f, 0.8f, 0.8f),// MaterialAmbientColor
			glm::vec3(0.9f, 0.9f, 0.9f),// MaterialDiffuseColor
			glm::vec3(0.9f, 0.9f, 0.9f),//MaterialSpecularColor
			0.6 * 128);
		break;
	case Gold:
		((Piece*)Objs->find(0)->second)->setLigthAttrs(
			glm::vec3(0.0, 0.0, 27.0),//pos 
			glm::vec2(0.0f, 0.0005f),//attenuation
			glm::vec3(0.24725, 0.1995, 0.0745),// AmbientLightColor
			glm::vec3(0.75164, 0.60648, 0.22648),// LightDiffuseColor
			glm::vec3(0.628281, 0.555802, 0.366065),// LightSpecularColor
			glm::vec3(0.8f, 0.8f, 0.8f),// MaterialAmbientColor
			glm::vec3(0.9f, 0.9f, 0.9f),// MaterialDiffuseColor
			glm::vec3(0.9f, 0.9f, 0.9f),//MaterialSpecularColor
			0.4 * 128);
		break;
	case Silver:
		((Piece*)Objs->find(0)->second)->setLigthAttrs(
			glm::vec3(0.0, 0.0, 27.0),//pos 
			glm::vec2(0.0f, 0.0005f),//attenuation
			glm::vec3(0.19225, 0.19225, 0.19225),// AmbientLightColor
			glm::vec3(0.50754, 0.50754, 0.50754),// LightDiffuseColor
			glm::vec3(0.508273, 0.508273, 0.508273),// LightSpecularColor
			glm::vec3(0.8f, 0.8f, 0.8f),// MaterialAmbientColor
			glm::vec3(0.9f, 0.9f, 0.9f),// MaterialDiffuseColor
			glm::vec3(0.9f, 0.9f, 0.9f),//MaterialSpecularColor
			0.4 * 128);
		break;
	case Esmerald:
		((Piece*)Objs->find(0)->second)->setLigthAttrs(
			glm::vec3(0.0, 0.0, 27.0),//pos 
			glm::vec2(0.0f, 0.0005f),//attenuation
			glm::vec3(0.0215, 0.1745, 0.0215),// AmbientLightColor
			glm::vec3(0.07568, 0.61424, 0.07568),// LightDiffuseColor
			glm::vec3(0.633, 0.727811, 0.633),// LightSpecularColor
			glm::vec3(0.8f, 0.8f, 0.8f),// MaterialAmbientColor
			glm::vec3(0.9f, 0.9f, 0.9f),// MaterialDiffuseColor
			glm::vec3(0.9f, 0.9f, 0.9f),//MaterialSpecularColor
			0.6*128);
		break;
	case Cyan :
		((Piece*)Objs->find(0)->second)->setLigthAttrs(
			glm::vec3(0.0, 0.0, 27.0),//pos 
			glm::vec2(0.0f, 0.0005f),//attenuation
			glm::vec3(0.0, 0.1, 0.06),// AmbientLightColor
			glm::vec3(0.0, 0.50980392, 0.50980392),// LightDiffuseColor
			glm::vec3(0.50196078, 0.50196078, 0.50196078),// LightSpecularColor
			glm::vec3(0.8f, 0.8f, 0.8f),// MaterialAmbientColor
			glm::vec3(0.9f, 0.9f, 0.9f),// MaterialDiffuseColor
			glm::vec3(0.9f, 0.9f, 0.9f),//MaterialSpecularColor
			0.25 * 128);
		break;
	default:
		break;
	}
}

void Manager::updateRotation()
{
	switch (rotation)
	{
	case NONE:
		break;
	case ROTX:
		manipulator->manipulatePiece((Piece*)Objs->find(0)->second, ROTATE, X_AXIS, 10);
		break;
	case ROTY:
		manipulator->manipulatePiece((Piece*)Objs->find(0)->second, ROTATE, Y_AXIS, 10);
		break;
	case ROTZ:
		manipulator->manipulatePiece((Piece*)Objs->find(0)->second, ROTATE, Z_AXIS, 10);
		break;
	default:
		break;
	}

}

ShaderProgram* Manager::createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	ShaderProgram *shProg = new ShaderProgram();

	shProg->addVertexShader(vertexShaderPath.c_str());
	shProg->addFragmentShader(fragmentShaderPath.c_str());

	glBindAttribLocation(shProg->getProgram(), VERTICES, "in_Position");
	glBindAttribLocation(shProg->getProgram(), COLORS, "in_Color");
	glBindAttribLocation(shProg->getProgram(), NORMALS, "in_Normal");
	glBindAttribLocation(shProg->getProgram(), TEXTURE, "in_Texture");
	shProg->link();

	return shProg;
}

void Manager::setTexFire()
{
	Piece * piece = (Piece*)Objs->find(0)->second;
	piece->getTexture()->load("..\\textures\\fire.tga");
}

void Manager::setTexStone()
{
	Piece * piece = (Piece*)Objs->find(0)->second;
	piece->getTexture()->load("..\\textures\\stone.tga");
}
