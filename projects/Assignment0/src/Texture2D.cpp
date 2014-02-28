#include "Texture2D.h"

Texture2D::Texture2D() : Texture()
{
	texture = new GLuint[1];
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::actBindTexture(int texChannel) 
{
	if (texChannel == 0)
	{
		glActiveTexture(GL_TEXTURE0);
	}
	else if (texChannel == 1)
	{
		glActiveTexture(GL_TEXTURE1);
	}
	glBindTexture(GL_TEXTURE_2D, texture[0]);
}

void Texture2D::load(const std::string& filename)
{
	texPath = filename;
	setType(GL_TEXTURE_2D);
	rgbType = GL_RGB;
	colorType = GL_RGB;
	
	glGenTextures(1, texture);
	image = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
	if(image==0)
	{
		std::cout << "error loading texture file" << filename << "." << std::endl;
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, rgbType, width, height, 0, colorType, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}