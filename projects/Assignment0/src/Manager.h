#pragma once

#include "Includes.h"
#include "ShaderProgram.h"
#include "Piece.h"
#include "Camera.h"
#include "Drawable.h"
#include "Texture2D.h"
#include "CubemapTexture.h"
#include "PieceReader.h"
#include "Manipulator.h"
#include "Skybox.h"

enum lightAttr { Default, Ruby, Gold, Silver, Esmerald, Cyan };

enum rotType { NONE, ROTX, ROTY, ROTZ };

class Manager
{
	int rotation;
	lightAttr lightAttrs;
	std::unordered_map<int, Drawable*> *Objs;

	Camera * camera;
	Manipulator * manipulator;
	Skybox *skybox;

	Manager() {};
	Manager(Manager const&);

public:
	static Manager& getInstance()
	{
		static Manager instance;
		return instance;
	}

	void initManager();
	void initScene();
	void initBumpedSphere();
	void draw();

	void updateCameraRotation(float x, float y);
	void updateCameraPosition(float x, float y);
	void updateCameraZoom(int amount);
	void updateLastMXY(float x, float y);
	void updateLightAttrs();

	void addGrid(float x, float y, float z, float size);
	void addSkybox();

	void incLightAttr();

	void transformPiece(int ID, int move, float tx);
	void setRotType(int rottype);
	void updateRotation();
	void setTexStone();
	void setTexFire();
	void updateLightPos(bool direction);

	Piece* getPiece(int ID);

	ShaderProgram *createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);

};