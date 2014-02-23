#pragma once

#include "Includes.h"
#include "ShaderProgram.h"
#include "Piece.h"
#include "Camera.h"
#include "Drawable.h"
#include "Texture2D.h"
#include "PieceReader.h"

class Manager
{
	std::vector<Drawable*> *Objs;
	Camera * camera;

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

	ShaderProgram *createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);

};