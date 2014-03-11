#include "Skybox.h"

Skybox::Skybox(void){}

Skybox::Skybox(ShaderProgram* prog, std::vector<Vertex> vertexes, int ident) : Piece(vertexes, prog, ident)
{

}

Skybox::~Skybox(void)
{

}

void Skybox::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraEye, glm::vec3 ligthpos)
{
	glm::mat4 m = createModelMatrix();

	ShaderProgram* shaderProg = shaderProg;
	GLuint VaoID = VaoId;
	GLuint progID = shaderProg->getProgram();

	GLint unifID = glGetUniformLocation(progID,"ModelMatrix");
	GLint uboID = glGetUniformBlockIndex(progID, "SharedMatrices");
	GLint drawSh = glGetUniformLocation(progID,"selected");

	glUniformBlockBinding(progID, uboID, shaderProg->getUBO_BP());

	GLuint* VboID = VboId;

	glBindBuffer(GL_UNIFORM_BUFFER, VboID[1]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &viewMatrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindVertexArray(VaoID);
	glUseProgram(progID);

	glUniformMatrix4fv(unifID, 1, GL_TRUE, glm::value_ptr(m));	

	glUniform1i(glGetUniformLocation(progID, "u_cubemap"), 0);
	
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, vertexes.size());
	glEnable(GL_DEPTH_TEST);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}