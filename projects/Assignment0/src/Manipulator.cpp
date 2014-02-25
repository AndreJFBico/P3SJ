#include "Manipulator.h"

#include <iostream>

Manipulator::Manipulator(){}

void Manipulator::manipulatePiece(Piece* piece, int manipulation, int axis, float howmuch)
{
	switch (manipulation)
	{
	case 0: 
		rotate(piece, axis, howmuch);
		break;
	case 1: 
		translate(piece, axis, howmuch);
		break;
	case 2:
		scale(piece, axis, howmuch);
		break;

	default:
		std::cerr << "Piece manipulation not valid" << std::endl;
		break;
	}
}

void Manipulator::rotate(Piece* piece, int axis, float degrees)
{
	float v = 0.02f;
	if(degrees < 0)
		v = -0.02f;

	glm::vec3 direction;
	switch (axis)
	{
	case 0:
		direction = glm::vec3(v, 0.0f, 0.0f);
		break;
	case 1:
		direction = glm::vec3(0.0f, v, 0.0f);
		break;
	case 2:
		direction = glm::vec3(0.0, 0.0f, v);
		break;
	default:
		std::cerr << "Invalid axis" << std::endl;
		break;
	}
	float fAngRad = glm::radians(degrees);
    glm::vec3 ax = glm::normalize(direction); 
    ax = ax * sinf(fAngRad / 2.0f);
    float scalar = cosf(fAngRad / 2.0f); 
    glm::fquat offset(scalar, direction.x, direction.y, direction.z);   
    piece->setOrientation( glm::normalize( piece->getOrientation()* offset ) );
}

void Manipulator::translate(Piece* piece, int axis, float distance)
{
	glm::vec3 direction;
	switch (axis)
	{
	case 0:
		direction = glm::vec3(distance, 0.0f, 0.0f);
		break;
	case 1:
		direction = glm::vec3(0.0f, distance, 0.0f);
		break;
	case 2:
		direction = glm::vec3(0.0, 0.0f, distance);
		break;
	default:
		std::cerr << "Invalid axis" << std::endl;
		break;
	}
	piece->addTransformation(glm::transpose(glm::translate(glm::mat4(1.0f), direction)));
}

void Manipulator::scale(Piece* piece, int axis, float size)
{
	glm::vec3 direction;
	switch (axis)
	{
	case 0:
		direction = glm::vec3(1.0f+size, 1.0f, 1.0f);
		break;
	case 1:
		direction = glm::vec3(1.0f, 1.0f+size, 1.0f);
		break;
	case 2:
		direction = glm::vec3(1.0, 1.0f, 1.0f+size);
		break;
	default:
		std::cerr << "Invalid axis" << std::endl;
		break;
	}
	piece->addScaleTransformation(glm::transpose(glm::scale(glm::mat4(1.0f), direction)));
}

Manipulator::~Manipulator(){}
