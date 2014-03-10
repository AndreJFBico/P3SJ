#pragma once
#include "Includes.h"
#include "Textures.h"
#include "SOIL\SOIL.h"

class CubemapTexture : public Texture
{

public:
	CubemapTexture();
	void load(const std::string& filename);
	void loadmipmap();
	void bind();
	void actBindTexture();

};