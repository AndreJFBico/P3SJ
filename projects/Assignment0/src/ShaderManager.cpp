#include "ShaderManager.h"

ShaderManager::ShaderManager(void)
{
	programsList = std::map<std::string, ShaderProgram*>();
}

void ShaderManager::addShaderProgram(std::string name, ShaderProgram *program){
	programsList.insert(std::pair<std::string, ShaderProgram*>(name, program));
}

ShaderProgram* ShaderManager::getShaderProgram(std::string name){
	return programsList[name];
}

void ShaderManager::removeShaderProgram(std::string name){
	std::map<std::string, ShaderProgram*>::iterator it;
	it=programsList.find(name);
	programsList.erase(it);
}

void ShaderManager::destroyShaders() {
	programsList.clear();
	programsList = std::map<std::string, ShaderProgram*>();
}

ShaderManager::~ShaderManager(void)
{
}
