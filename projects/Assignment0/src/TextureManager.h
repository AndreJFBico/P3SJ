#pragma once
#include "Includes.h"
#include "Textures.h"

class TextureManager {
	std::map<std::string, Texture*> textures;

public:
	TextureManager(void){};
	~TextureManager(void){};

	void add(std::string key, Texture* t){
		textures.insert(std::pair<std::string, Texture*>(key, t));
	}

	void remove(std::string key){
		std::map<std::string, Texture*>::iterator it;
		it = textures.find(key);
		textures.erase(it);
	}

	Texture* get(std::string key){
		std::map<std::string, Texture*>::iterator it;
		it = textures.find(key);
		return it->second;
	}

};

