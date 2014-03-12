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

out vec3 reflected;

void main () {
	
	mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	mat4 ModelViewProjectionMatrixMatrix = ProjectionMatrix * ModelMatrix;
	vec4 MCVertex = in_Position;
	ex_Vertex = (ModelViewMatrix * MCVertex);
	ex_Normal = normalize(NormalMatrix * vec3(in_Normal));
	ex_Texcoord = vec2(in_Texture.x, 1.0-in_Texture.y);;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCVertex;
  	
  	/*vec3 pos_eye = vec3 (ModelViewMatrix * in_Position);
 	vec3 n_eye = vec3(NormalMatrix * vec3(in_Normal));

 	vec3 incident_eye = normalize (pos_eye);
  	vec3 normal = normalize (n_eye);*/
  	vec3 incident_eye = normalize((ModelMatrix * MCVertex).xyz - cameraEye);
	vec3 g = reflect(incident_eye, normalize(mat3(transpose(inverse(ModelMatrix)))*(vec3(in_Normal))));
	reflected = vec3(g.x, -g.yz);
  	//reflected = normalize(reflect (incident_eye, normal));
}