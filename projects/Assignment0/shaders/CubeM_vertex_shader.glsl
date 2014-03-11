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

out vec3 reflected;
out vec3 texcoordT;

void main () {
	
	mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	mat4 ModelViewProjectionMatrixMatrix = ProjectionMatrix * ModelMatrix;
	vec4 MCVertex = in_Position;
	ex_Vertex = (ModelViewMatrix * MCVertex);
	ex_Normal = normalize(NormalMatrix * vec3(in_Normal));
	ex_Texcoord = vec2(in_Texture.x, 1.0-in_Texture.y);;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCVertex;

	
	vec3 incident_eye = normalize(vec3((ModelMatrix * MCVertex) - vec4(cameraEye, 1.0)));
	reflected = reflect(incident_eye, vec3(normalize(transpose(inverse(ModelMatrix))*(in_Normal))));
	texcoordT = vec3(ModelMatrix * MCVertex);
}