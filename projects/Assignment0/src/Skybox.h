#pragma once
#include "Includes.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Piece.h"

class Skybox : public Piece
{

public:
	Skybox(void);
	Skybox(ShaderProgram* prog, std::vector<Vertex> vertexes, int ident);
	~Skybox(void);

	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye, glm::vec3 ligthpos);
};

