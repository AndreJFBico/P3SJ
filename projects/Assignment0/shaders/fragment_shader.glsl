#version 330 core

in vec4 ex_Vertex;
in vec3 ex_Normal;
in vec2 ex_Texcoord;
in vec4 ex_Color;

out vec4 colorOut;

void main(void)
{
	colorOut = ex_Color;
}
