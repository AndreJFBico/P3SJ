///////////////////////////////////////////////////////////////////////
//	P3SJ - Assignment 0
// 
//
///////////////////////////////////////////////////////////////////////
#include "Includes.h"
#include "Manager.h"
#include "Interface.h"

#define CAPTION "P3SJ"

int WinX = WINDOW_WIDTH, WinY = WINDOW_HEIGHT;
unsigned int FrameCount = 0;

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	Manager::getInstance().draw();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void onMouse(int button, int state, int x, int y) {
	Interface::getInstance().onMouse(button, state, x, y);
}

void mouseWheel(int button, int dir, int x, int y)
{
	Interface::getInstance().displayWindow();
	Interface::getInstance().mouseWheel(button, dir, x, y);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	Interface::getInstance().KeyboardFunc(key, x, y);
}

void specialkeyPressed(int key, int x, int y)
{
	Interface::getInstance().specialkeyPressed(key, x, y);
}

void passiveMotionFunc(int x, int y)
{
	Interface::getInstance().passiveMotionFunc(x, y);
}

void reDraw(int value) {
	glutPostRedisplay();
	glutTimerFunc(16, reDraw, 0);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	Interface::getInstance().displayWindow();
	glutSetWindowTitle(s.c_str());
	glutPostRedisplay();
	FrameCount = 0;
	glutTimerFunc(1000, timer, 0);
}

void setupCallbacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, reDraw, 0);
	glutTimerFunc(0, timer, 0);
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(specialkeyPressed);
	glutPassiveMotionFunc(passiveMotionFunc);
	glutMouseFunc(onMouse);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	/* Configuration of the Open GL renderer */
	/*Enable back face culling*/
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	/*--------------------*/

	/*Blending*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*--------------------*/

	/* Depth buffer setup */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	/*--------------------*/

	/* Stencil buffer setup */
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearStencil(0.0);
	/*--------------------*/
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	Interface::getInstance().initInterface(glutCreateWindow(CAPTION));
	if (Interface::getInstance().getWindowHandle() < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCallbacks();
	Manager::getInstance().initManager();
	Manager::getInstance().initScene();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}