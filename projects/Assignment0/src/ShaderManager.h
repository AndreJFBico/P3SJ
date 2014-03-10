#pragma once
#include "Includes.h"
#include "ShaderProgram.h"
class ShaderManager
{
private:
	std::map<std::string, ShaderProgram*> programsList;
public:
	ShaderManager(void);

	void addShaderProgram(std::string name, ShaderProgram *shaderProgram);
	void removeShaderProgram(std::string name);
	void destroyShaders();

	ShaderProgram* getShaderProgram(std::string name);

	~ShaderManager(void);
};

