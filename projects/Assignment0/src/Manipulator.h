#pragma once

#include "Piece.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

class Manipulator
{
public:
	Manipulator();

	void manipulatePiece(Piece* piece, int manipulation, int axis, float howmuch);

	/*	
		TRANSFORMATIONS
	*/
	void rotate(Piece* piece, int axis, float degrees);
	void translate(Piece* piece, int axis, float distance);
	void scale(Piece* piece, int axis, float size);

	virtual ~Manipulator();
};

