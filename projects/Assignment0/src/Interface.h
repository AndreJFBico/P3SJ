#pragma once

#include "Includes.h"
#include "Manager.h"



class Interface
{
	int WindowHandle, rotationMode;
	bool cameraMode;

	Interface() {};
	Interface(Interface const&);

public:
	static Interface& getInstance()
	{
		static Interface instance;
		return instance;
	}

	void initInterface(int val);

	void setWindowHandle(int val);
	int getWindowHandle();

	void displayWindow();

	void onMouse(int button, int state, int x, int y);
	void mouseWheel(int button, int dir, int x, int y);
	void KeyboardFunc(unsigned char key, int x, int y);
	void specialkeyPressed(int key, int x, int y);
	void passiveMotionFunc(int x, int y);
};