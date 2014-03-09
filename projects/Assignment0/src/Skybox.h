#pragma once
#include "Includes.h"
#include "ShaderProgram.h"
#include "Vertex.h"

class Skybox
{
	glm::fquat orientation;
	glm::mat4 transformation;
	glm::mat4 center;

	std::vector<Vertex> Vertexes;

	GLuint VaoId, VboId[2];
	ShaderProgram* shaderProg;

public:
	Skybox(void);
	Skybox(ShaderProgram* prog, std::vector<Vertex> vertexes);
	~Skybox(void);

	///GETTERS & SETTERS
	std::vector<Vertex> getVertexes(){ return Vertexes;}
	Vertex getVertex(int i){ return Vertexes[i];}
	GLuint getVaoID(){ return VaoId;}
	GLuint* getVboID(){ return VboId;}

	ShaderProgram* getShaderProgram(){ return shaderProg;}
	void setShaderProgram(ShaderProgram* prog){ shaderProg = prog;}

	///FUNCOES
	void createBufferObject(); 
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye, glm::vec3 ligthpos);
	void addTransformation(glm::mat4 m); 
	void addCenterTransformation(glm::mat4 m);
	glm::mat4 createModelMatrix(); 
	glm::fquat getOrientation() {return orientation;}
	void setOrientation(glm::fquat v) {orientation = v;}
	void addVertex(Vertex v){ Vertexes.push_back(v);}
};

