#include "Camera.h"

Camera::Camera()
{
	center = glm::vec3(0,0,-5);
	last_mx = 0, last_my = 0;
	RotationAngleX = 0;
	RotationAngleY = 0;
	createViewMatrix(0, 0, -5);
}

void Camera::setPerspective(float fovy, float aspect, float zNear, float zFar) 
{ 
	ProjectionMatrix = glm::perspective(fovy, aspect, zNear, zFar); 
}

void Camera::setOrtogonal(float Left, float  Right, float Bottom, float Top, float Near, float Far)
{
	ProjectionMatrix = glm::ortho(Left, Right, Bottom, Top, Near, Far);
}

void Camera::OffsetOrientation(glm::vec3 &_axis, float fAngDeg)
{
	float fAngRad = glm::radians(fAngDeg);

	glm::vec3 axis = glm::normalize(_axis);

	axis = axis * sinf(fAngRad / 2.0f);
	float scalar = cosf(fAngRad / 2.0f);

	glm::fquat offset(scalar, axis.x, axis.y, axis.z);

	orientation = offset * orientation;

	orientation = glm::normalize(orientation);
}

glm::vec3 Camera::computeCameraCenter()
{
	glm::vec3 r = glm::vec3(glm::vec4(center.x, center.y, center.z, 0.0) * glm::mat4_cast(orientation));
	return glm::vec3(-r.x, -r.y, -r.z);
}

void Camera::createViewMatrix( float centerx, float centery, float centerz)
{
	OffsetOrientation(glm::vec3(1.0f, 0.0f, 0.0f),RotationAngleX);
	OffsetOrientation(glm::vec3(0.0f, 1.0f, 0.0f),RotationAngleY);
	glm::mat4 T = glm::translate(glm::mat4(1.f), glm::vec3(0.0, 0.0, centerz));
	glm::mat4 C = glm::translate(glm::mat4(1.f), glm::vec3(centerx, centery, 0.0));
	ViewMatrix = T*glm::mat4_cast(orientation)*C;
	RotationAngleX = 0;
	RotationAngleY = 0;
	updateOrientation = false;
}

void Camera::updateCamera()
{
	createViewMatrix(center.x, center.y, center.z);
}

//Setters
void Camera::setCenter(glm::vec3 v)
{
	center = v;
	updateCamera();
}

void Camera::setLast_mx(float x)
{
	last_mx = x;
}

void Camera::setLast_my(float y)
{
	last_my = y;
}

void Camera::setRotationAngleX(float x)
{
	RotationAngleX = x;
}

void Camera::setRotationAngleY(float y)
{
	RotationAngleY = y;
}

//Getters
glm::vec3 Camera::getCenter() 
{
	return center;
}

glm::mat4 Camera::getOrientation()
{
	return glm::mat4_cast(orientation);
}

int Camera::getLast_mx() 
{
	return last_mx;
}

int Camera::getLast_my()
{
	return last_my;
}

glm::mat4 Camera::getViewMatrix() 
{
	return ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() 
{
	return ProjectionMatrix;
}

float Camera::getRotationAngleX()
{
	return RotationAngleX;
}

float Camera::getRotationAngleY()
{
	return RotationAngleY;
}

glm::fquat Camera::getQuatOrientation()
{
	return orientation;
}

//Destructor
Camera::~Camera(void)
{
}