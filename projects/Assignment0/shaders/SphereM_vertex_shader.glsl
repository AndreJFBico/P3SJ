#version 330 core

uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

uniform vec3 cameraEye;

in vec4 in_Position;
in vec4 in_Color;
in vec4 in_Normal;
in vec2 in_Texture;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

out vec4 ex_Vertex;
out vec3 ex_Normal;
out vec2 ex_Texcoord;
out vec4 ex_Color;

void main () {
	mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;

	vec3 Vertex = vec3(ModelViewMatrix * in_Position);
	vec3 n = normalize(NormalMatrix * vec3(in_Normal));
	vec3 e = vec3(0.0, 0.0, -1.0);
	
	vec3 u = normalize(Vertex);
	vec3 r = e - 2*n*(dot(n, e));
	float p = sqrt(2.0*(r.z + 1.0));
	float s = r.x/(2.0*p) + 0.5;
	float t = r.y/(2.0*p) + 0.5;

	ex_Vertex = (ModelViewMatrix * in_Position);
	ex_Normal = normalize(NormalMatrix * vec3(in_Normal));
	ex_Texcoord = vec2(s, t);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	ex_Color = in_Color;
} 