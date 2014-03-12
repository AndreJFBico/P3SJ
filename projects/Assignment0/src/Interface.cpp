#include "Interface.h"

void Interface::initInterface(int val)
{
	WindowHandle = val;
	cameraMode = false;
	rotationMode = NONE;
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
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Manager::getInstance().setRotType(ROTX);
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Manager::getInstance().setRotType(ROTY);
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		Manager::getInstance().setRotType(ROTZ);
	}
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
	else if (key == 's')
	{
		Manager::getInstance().setTexStone();
	}
	else if (key == 'f')
	{
		Manager::getInstance().setTexFire();
	}
	else if (key == 'm')
	{
		Manager::getInstance().incLightAttr();
	}
	else if (key == 'k')
	{
		Manager::getInstance().updateLightPos(0);
	}
	else if (key == 'i')
	{
		Manager::getInstance().updateLightPos(1);
	}
	else if (key == 'u')
	{
		Manager::getInstance().updateLightPos(2);
	}
	else if (key == 'o')
	{
		Manager::getInstance().updateLightPos(3);
	}
	else if (key == 'l')
	{
		Manager::getInstance().updateLightPos(4);
	}
	else if (key == 'j')
	{
		Manager::getInstance().updateLightPos(5);
	}
	else if (key == 'n')
	{
		Manager::getInstance().setPieceNoTex();
	}
	else if (key == 'q')
	{
		Manager::getInstance().incScene();
	}
}

void Interface::specialkeyPressed(int key, int x, int y)
{
	x = x - WINDOW_WIDTH / 2.0f;
	y = -(y - WINDOW_HEIGHT / 2.0f);
	if (key == GLUT_KEY_LEFT)
	{
		Manager::getInstance().updateCameraPosition(x, y);
		Manager::getInstance().updateLastMXY(x, y);
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		Manager::getInstance().updateCameraPosition(x, y);
		Manager::getInstance().updateLastMXY(x, y);
	}
	else if (key == GLUT_KEY_UP)
	{
		Manager::getInstance().updateCameraPosition(x, y);
		Manager::getInstance().updateLastMXY(x, y);
	}
	else if (key == GLUT_KEY_DOWN)
	{
		Manager::getInstance().updateCameraPosition(x, y);
		Manager::getInstance().updateLastMXY(x, y);
	}
	Manager::getInstance().updateLastMXY(x, y);
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