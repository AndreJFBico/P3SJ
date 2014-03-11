#include "Piece.h"

Piece::Piece() : Drawable() {}

Piece::Piece(std::vector<Vertex> vs, std::vector<unsigned int> is, ShaderProgram* prog, int ident) : Drawable()
{
	id = ident;
	vertexes = vs;
	indices = is;
	shaderProg = prog;
	scale = glm::mat4(1.0f);
	initTransformation = glm::mat4(1.0f);
	transformation = glm::mat4(1.0f);
	setLigthAttrs(	
	glm::vec3(0.0, 0.0, 27.0),
	glm::vec2(0.0f, 0.0005f),
	glm::vec3(0.1f, 0.3f, 0.3f),
	glm::vec3(0.9f, 0.9f, 0.9f),
	glm::vec3(0.9f, 0.9f, 0.9f),
	glm::vec3(0.8f, 0.8f, 0.8f),
	glm::vec3(0.9f, 0.9f, 0.9f),
	glm::vec3(0.9f, 0.9f, 0.9f),
	64.0f);
	tex = 0;
	tex1 = 0;
	genTangentVec();
	createBufferObject();
	variation = 0.0;
	setLines = false;
}

Piece::Piece(std::vector<Vertex> vs, std::vector<unsigned int> is, ShaderProgram* prog, Texture* t, Texture* t1,int ident) : Drawable()
{
	id = ident;
	vertexes = vs;
	indices = is;
	shaderProg = prog;
	scale = glm::mat4(1.0f);
	initTransformation = glm::mat4(1.0f);
	transformation = glm::mat4(1.0f);
	tex = t;
	tex1 = t1;
	setLigthAttrs(	
	glm::vec3(0.0, 0.0, 27.0),
	glm::vec2(0.0f, 0.0005f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.9f, 0.9f, 0.9f),
	glm::vec3(0.9f, 0.9f, 0.9f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.8f, 0.8f, 0.8f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	64.0f);
	genTangentVec();
	createBufferObject();
	variation = 0.0;
	setLines = false;
}

void Piece::genTangentVec()
{
	if (tex1 != 0)
	{
		for (int i = 0; i < vertexes.size(); i += 3)
		{
			Vertex* v1 = &vertexes.at(i);
			Vertex* v2 = &vertexes.at(i+1);
			Vertex* v3 = &vertexes.at(i+2);


			glm::vec2 w1 = v1->UV;
			glm::vec2 w2 = v2->UV;
			glm::vec2 w3 = v3->UV;

			float x1 = v2->XYZW.x - v1->XYZW.x;
			float x2 = v3->XYZW.x - v1->XYZW.x;
			float y1 = v2->XYZW.y - v1->XYZW.y;
			float y2 = v3->XYZW.y - v1->XYZW.y;
			float z1 = v2->XYZW.z - v1->XYZW.z;
			float z2 = v3->XYZW.z - v1->XYZW.z;

			float s1 = w2.x - w1.x;
			float s2 = w3.x - w1.x;
			float t1 = w2.y - w1.y;
			float t2 = w3.y - w1.y;

			float r = 1.0F / (s1 * t2 - s2 * t1);
			glm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
				(t2 * z1 - t1 * z2) * r);
			glm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
				(s1 * z2 - s2 * z1) * r);

			glm::vec4 tg = glm::vec4(glm::normalize(sdir - glm::vec3(v1->NORMAL) * glm::dot(glm::vec3(v1->NORMAL), sdir)), 0.0);
			tg.w = glm::dot(glm::cross(glm::vec3(v1->NORMAL), sdir), tdir);
			if (tg.w < 0.0f)
				tg.w = -1.0;
			else tg.w = 1.0f;
			v1->TANG = tg;

			tg = glm::vec4(glm::normalize(sdir - glm::vec3(v2->NORMAL) * glm::dot(glm::vec3(v2->NORMAL), sdir)), 0.0);
			tg.w = glm::dot(glm::cross(glm::vec3(v2->NORMAL), sdir), tdir);
			if (tg.w < 0.0f)
				tg.w = -1.0;
			else tg.w = 1.0f;
			v2->TANG = tg;

			tg = glm::vec4(glm::normalize(sdir - glm::vec3(v3->NORMAL) * glm::dot(glm::vec3(v3->NORMAL), sdir)), 0.0);
			tg.w = glm::dot(glm::cross(glm::vec3(v3->NORMAL), sdir), tdir);
			if (tg.w < 0.0f)
				tg.w = -1.0;
			else tg.w = 1.0f;
			v3->TANG = tg;
			
			v1->TANG = glm::vec4(0.0, 1.0, 0.0, 1.0);
			v2->TANG = glm::vec4(0.0, 1.0, 0.0, 1.0);
			v3->TANG = glm::vec4(0.0, 1.0, 0.0, 1.0);
			/*glm::vec4 Edge1 = vertexes.at(i + 1).XYZW - vertexes.at(i).XYZW;
			glm::vec4 Edge2 = vertexes.at(i + 2).XYZW - vertexes.at(i).XYZW;

			float DeltaU1 = vertexes.at(i + 1).UV.x - vertexes.at(i).UV.x;
			float DeltaV1 = vertexes.at(i + 1).UV.y - vertexes.at(i).UV.y;
			float DeltaU2 = vertexes.at(i + 2).UV.x - vertexes.at(i).UV.x;
			float DeltaV2 = vertexes.at(i + 2).UV.y - vertexes.at(i).UV.y;

			float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);
			glm::vec4 Tangent;
			glm::vec3 Bitangent;
			Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
			Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
			Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

			Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
			Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
			Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

			// Gram-Schmidt orthogonalize
			vertexes.at(i).TANG = Tangent - (glm::dot((vertexes.at(i).NORMAL), Tangent))* (vertexes.at(i).NORMAL);
			vertexes.at(i + 1).TANG = Tangent - (glm::dot((vertexes.at(i + 1).NORMAL), Tangent))* (vertexes.at(i + 1).NORMAL);
			vertexes.at(i + 2).TANG = Tangent - (glm::dot((vertexes.at(i + 2).NORMAL), Tangent))* (vertexes.at(i + 2).NORMAL);
		
			vertexes.at(i).TANG = glm::normalize(vertexes.at(i).TANG - vertexes.at(i).NORMAL * (glm::dot(vertexes.at(i).NORMAL, vertexes.at(i).TANG)));
			vertexes.at(i + 1).TANG = glm::normalize(vertexes.at(i + 1).TANG - vertexes.at(i + 1).NORMAL * (glm::dot(vertexes.at(i + 1).NORMAL, vertexes.at(i + 1).TANG)));
			vertexes.at(i + 2).TANG = glm::normalize(vertexes.at(i + 2).TANG - vertexes.at(i + 2).NORMAL * (glm::dot(vertexes.at(i + 2).NORMAL, vertexes.at(i + 2).TANG)));

			//handeness
			vertexes.at(i).TANG.w = glm::dot(glm::cross(glm::vec3(vertexes.at(i).NORMAL), glm::vec3(vertexes.at(i).TANG)), Bitangent);
			vertexes.at(i + 1).TANG.w = glm::dot(glm::cross(glm::vec3(vertexes.at(i + 1).NORMAL), glm::vec3(vertexes.at(i + 1).TANG)), Bitangent);
			vertexes.at(i + 2).TANG.w = glm::dot(glm::cross(glm::vec3(vertexes.at(i + 2).NORMAL), glm::vec3(vertexes.at(i + 2).TANG)), Bitangent);*/
		}
	}
}

Drawable* Piece::clone()
{
	return 0;
}

void Piece::setLigthAttrs(	
	glm::vec3 LightPosition, 
	glm::vec2 LightAttenuation,
	glm::vec3 AmbientLightColor,
	glm::vec3 LightDiffuseColor,
	glm::vec3 LightSpecularColor,
	glm::vec3 MaterialAmbientColor,
	glm::vec3 MaterialDiffuseColor,
	glm::vec3 MaterialSpecularColor,
	float MaterialShininess)
{
	progID = shaderProg->getProgram();

	glUseProgram(progID);

	glUniform3f(glGetUniformLocation(progID, "LightPosition"), LightPosition.x, LightPosition.y, LightPosition.z);
	lightPos = LightPosition;
	glUniform2f(glGetUniformLocation(progID, "LightAttenuation"), LightAttenuation.x, LightAttenuation.y);
	glUniform3f(glGetUniformLocation(progID, "AmbientLightColor"), AmbientLightColor.x, AmbientLightColor.y, AmbientLightColor.z);
	glUniform3f(glGetUniformLocation(progID, "LightDiffuseColor"), LightDiffuseColor.x, LightDiffuseColor.y, LightDiffuseColor.z);
	glUniform3f(glGetUniformLocation(progID, "LightSpecularColor"), LightSpecularColor.x, LightSpecularColor.y, LightSpecularColor.z);

	glUniform3f(glGetUniformLocation(progID, "MaterialAmbientColor"), MaterialAmbientColor.x, MaterialAmbientColor.y, MaterialAmbientColor.z);
	glUniform3f(glGetUniformLocation(progID, "MaterialDiffuseColor"), MaterialDiffuseColor.x, MaterialDiffuseColor.y, MaterialDiffuseColor.z);
	glUniform3f(glGetUniformLocation(progID, "MaterialSpecularColor"), MaterialSpecularColor.x, MaterialSpecularColor.y, MaterialSpecularColor.z);
	glUniform1f(glGetUniformLocation(progID, "MaterialShininess"), MaterialShininess);

	glUniform1i(glGetUniformLocation(progID, "u_cubemap"), 1);
}

void Piece::setLigthAttrs(
	glm::vec2 LightAttenuation,
	glm::vec3 AmbientLightColor,
	glm::vec3 LightDiffuseColor,
	glm::vec3 LightSpecularColor,
	glm::vec3 MaterialAmbientColor,
	glm::vec3 MaterialDiffuseColor,
	glm::vec3 MaterialSpecularColor,
	float MaterialShininess)
{
	progID = shaderProg->getProgram();

	glUseProgram(progID);

	glUniform2f(glGetUniformLocation(progID, "LightAttenuation"), LightAttenuation.x, LightAttenuation.y);
	glUniform3f(glGetUniformLocation(progID, "AmbientLightColor"), AmbientLightColor.x, AmbientLightColor.y, AmbientLightColor.z);
	glUniform3f(glGetUniformLocation(progID, "LightDiffuseColor"), LightDiffuseColor.x, LightDiffuseColor.y, LightDiffuseColor.z);
	glUniform3f(glGetUniformLocation(progID, "LightSpecularColor"), LightSpecularColor.x, LightSpecularColor.y, LightSpecularColor.z);

	glUniform3f(glGetUniformLocation(progID, "MaterialAmbientColor"), MaterialAmbientColor.x, MaterialAmbientColor.y, MaterialAmbientColor.z);
	glUniform3f(glGetUniformLocation(progID, "MaterialDiffuseColor"), MaterialDiffuseColor.x, MaterialDiffuseColor.y, MaterialDiffuseColor.z);
	glUniform3f(glGetUniformLocation(progID, "MaterialSpecularColor"), MaterialSpecularColor.x, MaterialSpecularColor.y, MaterialSpecularColor.z);
	glUniform1f(glGetUniformLocation(progID, "MaterialShininess"), MaterialShininess);
}

void Piece::setLigthPos(bool direction)
{
	progID = shaderProg->getProgram();

	glUseProgram(progID);

	if (direction){
		glUniform3f(glGetUniformLocation(progID, "LightPosition"), lightPos.x, lightPos.y, lightPos.z + 1.0);
		lightPos = glm::vec3(lightPos.x, lightPos.y, lightPos.z + 1.0);
	}
	else{
		glUniform3f(glGetUniformLocation(progID, "LightPosition"), lightPos.x, lightPos.y, lightPos.z - 1.0);
		lightPos = glm::vec3(lightPos.x, lightPos.y, lightPos.z - 1.0);
	}
}

void Piece::createBufferObject()
{
	unifID = glGetUniformLocation(progID, "ModelMatrix");
	normalID = glGetUniformLocation(progID, "NormalMatrix");
	uboID = glGetUniformBlockIndex(progID, "SharedMatrices");

	glUniformBlockBinding(progID, uboID, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(2, VboId);

	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexes.size(), &vertexes[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(vertexes[0].XYZW));

	glEnableVertexAttribArray(NORMALS);
	glVertexAttribPointer(NORMALS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(vertexes[0].XYZW) + sizeof(vertexes[0].RGBA)));

	glEnableVertexAttribArray(TEXTURE);
	glVertexAttribPointer(TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(vertexes[0].XYZW) + sizeof(vertexes[0].RGBA) + sizeof(vertexes[0].NORMAL)));

	glEnableVertexAttribArray(TANGENT);
	glVertexAttribPointer(TANGENT, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(vertexes[0].XYZW) + sizeof(vertexes[0].RGBA) + sizeof(vertexes[0].NORMAL) + sizeof(vertexes[0].UV)));

	glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, VboId[1]);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Piece::prepareDraw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye)
{
	glBindVertexArray(VaoId);
	glUseProgram(progID);

	glUniform3f(glGetUniformLocation(progID, "cameraEye"), cameraEye.x, cameraEye.y, cameraEye.z);

	glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &viewMatrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	if (tex != 0 && tex1 != 0)
	{
		tex->actBindTexture(0);
		glUniform1i(glGetUniformLocation(progID, "Texture0"), 0);
		tex1->actBindTexture(1);
		glUniform1i(glGetUniformLocation(progID, "Texture1"), 1);
		glUniform1f(glGetUniformLocation(progID, "textured"), true);
	}
	else if (tex != 0 )
	{
		tex->actBindTexture(0);
		glUniform1f(glGetUniformLocation(progID, "textured"), true);
		glUniform1i(glGetUniformLocation(progID, "Texture0"), 0);
	}
	else if (tex1 != 0)
	{
		tex1->actBindTexture(1);
		glUniform1f(glGetUniformLocation(progID, "textured"), true);
		glUniform1i(glGetUniformLocation(progID, "Texture0"), 1);
	}
	else
	{
		glUniform1f(glGetUniformLocation(progID, "textured"), false);
	}
}

void Piece::sendModelMatrix(glm::mat4 viewMatrix, glm::mat4 modelMatrix)
{
	glUniformMatrix4fv(unifID, 1, GL_TRUE, glm::value_ptr(modelMatrix));
	//15% performance hazard due to inverse plus 2 transposes
	glUniformMatrix3fv(normalID, 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(viewMatrix * glm::transpose(modelMatrix))))));
}

void Piece::bindDraw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	if (!setLines) {
		glDrawElementsBaseVertex(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0, 0);
	}
	else glDrawElementsBaseVertex(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)0, 0);
	
}

void Piece::postDraw()
{
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Piece::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye)
{
	prepareDraw(viewMatrix, projectionMatrix, cameraEye);

	sendModelMatrix(viewMatrix, createModelMatrix());

	bindDraw();

	postDraw();
}

void Piece::addIndex(unsigned int v)
{
	indices.push_back(v);
}

int Piece::getID()
{
	return id;
}


void Piece::setId(int v)
{
	id = v;
}


glm::mat4 Piece::createModelMatrix()
{
	return  initTransformation  * glm::mat4_cast(orientation)* scale * transformation;
}

void Piece::setColor()
{
	for (std::vector<Vertex>::iterator it = vertexes.begin(); it != vertexes.end(); ++it)
	{
		it->RGBA[0] = 0.5;
		it->RGBA[1] = 0.5;
		it->RGBA[2] = 0.5;
	}
}

void Piece::setTransformation(glm::mat4 trans)
{
	transformation = trans;
}

void Piece::setOrientation(glm::fquat ori)
{
	orientation = ori;
}

glm::fquat Piece::getOrientation()
{
	return orientation;
}

glm::mat4 Piece::getTransformation()
{
	return transformation;
}

void Piece::reset()
{
	transformation = glm::mat4(1.0f);
}

void Piece::addTransformation(glm::mat4 m)
{
	transformation = transformation * m;
}

void Piece::addScaleTransformation(glm::mat4 m)
{
	scale = scale * m;
}

void Piece::noTex(){
	tex = 0;
	tex1 = 0;
}