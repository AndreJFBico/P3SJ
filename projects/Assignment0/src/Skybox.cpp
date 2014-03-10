#include "Skybox.h"

Skybox::Skybox(void){}

Skybox::Skybox(ShaderProgram* prog, std::vector<Vertex> vertexes) : shaderProg(prog)
{
	Vertexes = vertexes;
	createBufferObject();
	transformation = glm::mat4(1.0f);
	center = glm::mat4(1.0f);
}

Skybox::~Skybox(void)
{
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(2, VboId);

	glDeleteVertexArrays(1, &VaoId);
}

void Skybox::createBufferObject(){
	
	ShaderProgram* shaderProg = getShaderProgram();
	GLuint UBO_BP = shaderProg->getUBO_BP();

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(2, VboId);

	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec4)*3+sizeof(glm::vec2))*Vertexes.size(), &Vertexes[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(Vertexes[0].XYZW));

	glEnableVertexAttribArray(NORMALS);
	glVertexAttribPointer(NORMALS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(Vertexes[0].XYZW) + sizeof(Vertexes[0].RGBA)));
	
	glEnableVertexAttribArray(TEXTURE);
	glVertexAttribPointer(TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(Vertexes[0].XYZW) + sizeof(Vertexes[0].RGBA) +  sizeof(Vertexes[0].NORMAL)));

	glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId[1]);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glDisableVertexAttribArray(NORMALS);
}

void Skybox::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye, glm::vec3 ligthpos)
{
	glStencilFunc(GL_ALWAYS, 0, -1);
	glm::mat4 m = createModelMatrix();

	ShaderProgram* shaderProg = getShaderProgram();
	GLuint VaoID = getVaoID();
	GLuint progID = shaderProg->getProgram();

	GLint unifID = glGetUniformLocation(progID,"ModelMatrix");
	GLint uboID = glGetUniformBlockIndex(progID, "SharedMatrices");
	GLint drawSh = glGetUniformLocation(progID,"selected");

	glUniformBlockBinding(progID, uboID, shaderProg->getUBO_BP());

	GLuint* VboID = getVboID();

	glBindBuffer(GL_UNIFORM_BUFFER, VboID[1]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &viewMatrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindVertexArray(VaoID);
	glUseProgram(progID);

	glUniformMatrix4fv(unifID, 1, GL_TRUE, glm::value_ptr(m));	

	glUniform1i(glGetUniformLocation(progID, "u_cubemap"), 1);
	
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES,0,Vertexes.size());
	glEnable(GL_DEPTH_TEST);
	
	//glClearDepth(1.0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}

void Skybox::addTransformation(glm::mat4 m)
{
	transformation = transformation * m;
}

void Skybox::addCenterTransformation(glm::mat4 m)
{
	center = center * m;
}

glm::mat4 Skybox::createModelMatrix(){
	return  center * glm::mat4_cast(orientation) * transformation;
}