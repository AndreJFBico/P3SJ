#include "Interface.h"

void Interface::initInterface(int val)
{
	WindowHandle = val;
	cameraMode = false;
}

void Interface::displayWindow()
{
	glutSetWindow(WindowHandle);
}

int Interface::getWindowHandle()
{
	return WindowHandle;
}

void Interface::setWindowHandle(int val)
{
	WindowHandle = val;
}

void Interface::onMouse(int button, int state, int x, int y)
{
	/*
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

		GLUT_LEFT_BUTTON
			GLUT_MIDDLE_BUTTON
	}*/
}

void Interface::mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		Manager::getInstance().updateCameraZoom(y);
	}
	else
	{
		Manager::getInstance().updateCameraZoom(-y);
	}
	return;
}

void Interface::KeyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'c')
	{
		if (cameraMode)
		{
			glutSetCursor(GLUT_CURSOR_INHERIT);
			cameraMode = false;
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
			cameraMode = true;
		}
	}
}

void Interface::specialkeyPressed(int key, int x, int y)
{

}

void Interface::passiveMotionFunc(int x, int y)
{
	x = x - WINDOW_WIDTH / 2.0f;
	y = -(y - WINDOW_HEIGHT / 2.0f);
	if (cameraMode)
	{
		Manager::getInstance().updateCameraRotation(x, y);
	}
	Manager::getInstance().updateLastMXY(x, y);
}