#pragma once

#include "Includes.h"
#include "Vertex.h"
#include "Textures.h"
#include "ShaderProgram.h"
#include "Drawable.h"

class Piece : public Drawable
{

protected:
	int id;

	bool setLines, cubemapped;

	/*Variation on the current move towards the objective.*/
	float variation;
	/*Objective to move towards, changed by the method move.*/
	glm::vec3 objective;

	glm::fquat orientation;
	glm::mat4 scale;
	glm::mat4 initTransformation;
	glm::mat4 transformation;
	glm::vec3 lightPos;

	ShaderProgram* shaderProg;
	Texture * tex, * tex1;

	std::vector<Vertex> vertexes;
	std::vector<unsigned int> indices;

	GLuint VboId[2], VaoId, indexBuffer, progID;
	GLint unifID, normalID, uboID;

public:
	Piece();
	Piece(std::vector<Vertex> vs, std::vector<unsigned int> is, ShaderProgram* prog, int ident);
	Piece(std::vector<Vertex> vs, std::vector<unsigned int> is, ShaderProgram* prog, Texture* t, Texture* t1, int ident);
	Piece(std::vector<Vertex> vs, ShaderProgram* prog, int ident);

	Drawable* clone();

	void prepareDraw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye);
	virtual void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye);
	void sendModelMatrix(glm::mat4 viewMatrix, glm::mat4 modelMatrix);
	void bindDraw();
	void postDraw();
	void genTangentVec();

	void setLigthAttrs(	glm::vec3 LightPosition,
		glm::vec2 LightAttenuation,
		glm::vec3 AmbientLightColor,
		glm::vec3 LightDiffuseColor,
		glm::vec3 LightSpecularColor,
		glm::vec3 MaterialAmbientColor,
		glm::vec3 MaterialDiffuseColor,
		glm::vec3 MaterialSpecularColor,
		float MaterialShininess);

	void setLigthAttrs(glm::vec2 LightAttenuation,
		glm::vec3 AmbientLightColor,
		glm::vec3 LightDiffuseColor,
		glm::vec3 LightSpecularColor,
		glm::vec3 MaterialAmbientColor,
		glm::vec3 MaterialDiffuseColor,
		glm::vec3 MaterialSpecularColor,
		float MaterialShininess);

	void setLigthPos(int direction);

	void createBufferObject();
	void addIndex(unsigned int v);

	int getID();
	Texture* getTexture(){
		return tex;
	}

	void drawWithLines(){ setLines = true; }

	void transformCenter(glm::mat4 v) { initTransformation = initTransformation *v; }

	void setId(int id);
	void setColor();
	void setCubemapped(bool v);
	void setOrientation(glm::fquat orientation);
	void setTransformation(glm::mat4 transformation);

	void addTransformation(glm::mat4 m);
	void addScaleTransformation(glm::mat4 m);

	glm::fquat getOrientation();
	glm::mat4 getTransformation();

	void reset();
	void noTex();

	glm::mat4 createModelMatrix();
};