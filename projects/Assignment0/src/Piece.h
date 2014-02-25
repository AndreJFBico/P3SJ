#pragma once

#include "Includes.h"
#include "Vertex.h"
#include "Textures.h"
#include "ShaderProgram.h"
#include "Drawable.h"

class Piece : public Drawable
{

protected:
	int id, torque;

	/*Variation on the current move towards the objective.*/
	float variation;
	/*Objective to move towards, changed by the method move.*/
	glm::vec3 objective;

	glm::fquat orientation;
	glm::mat4 scale;
	glm::mat4 initTransformation;
	glm::mat4 transformation;

	ShaderProgram* shaderProg;
	Texture * tex;

	std::vector<Vertex> vertexes;
	std::vector<unsigned int> indices;

	GLuint VboId[2], VaoId, indexBuffer, progID;
	GLint unifID, normalID, uboID;

public:
	Piece();
	Piece(std::vector<Vertex> vs, std::vector<unsigned int> is, ShaderProgram* prog, int ident);
	Piece(std::vector<Vertex> vs, std::vector<unsigned int> is, ShaderProgram* prog, Texture* t, int ident);

	Drawable* clone();

	void prepareDraw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye);
	virtual void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye);
	void sendModelMatrix(glm::mat4 viewMatrix, glm::mat4 modelMatrix);
	void bindDraw();
	void postDraw();

	void createBufferObject();
	void addIndex(unsigned int v);

	int getID();
	int getTorque();

	void setId(int id);
	void setColor();
	void setOrientation(glm::fquat orientation);
	void setTransformation(glm::mat4 transformation);

	void addTransformation(glm::mat4 m);
	void addScaleTransformation(glm::mat4 m);

	void torquePiece(int axis);

	glm::fquat getOrientation();
	glm::mat4 getTransformation();

	void translate(glm::vec3 vec);
	void reset();

	glm::mat4 createModelMatrix();
};