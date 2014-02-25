#pragma once

#include "Includes.h"
#include "ShaderProgram.h"
#include "Piece.h"
#include "Camera.h"
#include "Drawable.h"
#include "Texture2D.h"
#include "PieceReader.h"
#include "Manipulator.h"


enum rotType { NONE, ROTX, ROTY, ROTZ };

class Manager
{
	int rotation;
	std::unordered_map<int, Drawable*> *Objs;
	Camera * camera;
	Manipulator * manipulator;

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
	void draw();

	void updateCameraRotation(float x, float y);
	void updateCameraPosition(float x, float y);
	void updateCameraZoom(int amount);
	void updateLastMXY(float x, float y);
	void transformPiece(int ID, int move, float tx);
	void setRotType(int rottype);
	void updateRotation();

	Piece* getPiece(int ID);

	ShaderProgram *createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);

};