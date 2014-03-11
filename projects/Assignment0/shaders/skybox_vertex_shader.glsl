#version 330 core

uniform mat4 ModelMatrix;

in vec4 in_Position;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

out vec3 texcoordT;

void main () {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;

	texcoordT = vec3(ModelMatrix * in_Position);
}