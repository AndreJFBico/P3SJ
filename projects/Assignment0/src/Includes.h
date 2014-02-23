#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include "GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define TEXTURE 3

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

#define tNEAR  0.1f
#define tFAR 4000.0f
#define tFOVY 30.0f
#define PI 3.141f