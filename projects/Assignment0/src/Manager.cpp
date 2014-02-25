#include "Manager.h"

void Manager::initManager()
{
	Objs = new std::unordered_map<int, Drawable*>;
	camera = new Camera();
	manipulator = new Manipulator();
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
}

void Manager::draw()
{
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