#version 330 core

uniform samplerCube u_cubemap;

/**/
in vec3 texcoordT;
/**/
out vec4 colorOut;

void main(void)
{
	colorOut = texture (u_cubemap, texcoordT);
}
