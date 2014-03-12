#version 330 core

uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

uniform vec3 cameraEye;

in vec4 in_Position;
in vec4 in_Color;
in vec4 in_Normal;
in vec2 in_Texture;
in vec4 in_Tangent;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

out vec4 ex_Vertex;
out vec3 ex_Normal;
out vec2 ex_Texcoord;
out vec4 ex_Color;

out vec3 tangN;
out vec3 tangT;
out vec3 tangB;

void main () {
	mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	ex_Vertex = (ModelViewMatrix * in_Position);
	ex_Normal = normalize(NormalMatrix * vec3(in_Normal));
	ex_Texcoord = vec2(in_Texture.x, 1.0- in_Texture.y);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	ex_Color = in_Color;

	//Building the matrix Eye Space -> Tangent Space
	tangN = ex_Normal;
	tangT = normalize(NormalMatrix * vec3(in_Tangent));
	tangB = in_Tangent.w * cross(tangN, tangT);
} 