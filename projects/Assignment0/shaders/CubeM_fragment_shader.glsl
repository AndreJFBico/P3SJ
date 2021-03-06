#version 330 core

uniform samplerCube u_cubemap;

uniform bool textured;

uniform vec3 LightPosition;
uniform vec2 LightAttenuation;
uniform vec3 AmbientLightColor;
uniform vec3 LightDiffuseColor;
uniform vec3 LightSpecularColor;

uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;
uniform float MaterialShininess;

uniform bool selected;
uniform int type;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

/**/
in vec3 reflected;
/**/

in vec4 ex_Vertex;
in vec3 ex_Normal;
in vec2 ex_Texcoord;
in vec4 ex_Color;

out vec4 colorOut;

void main(void)
{

	vec3 V = vec3(ex_Vertex);
	vec3 N = normalize(ex_Normal);
	
	vec3 Lpos = vec3(ViewMatrix * vec4(LightPosition, 1.0f));//luz em eyespace
	vec3 L = Lpos - V;
	float Ldist = length(L);
	L = normalize(L);
	vec3 E = normalize(-V);//eyespace a posi��o da camera � 0,0,0
	vec3 H = normalize(L + E);
	vec3 R = reflect(-L,N);//eyespace a posi��o da camera � 0,0,0
	
	vec3 ambient = AmbientLightColor * MaterialAmbientColor;//chega ao objecto de igual forma
	
	float NdotL = clamp(dot(N,L),0.0,1.0);
	vec3 diffuse = LightDiffuseColor * MaterialDiffuseColor * NdotL;
	//reflec��o especular
	
	vec3 specular = vec3(0.0);
	if(NdotL > 0.0) {
		float NdotH = clamp(dot(R,H),0.0,1.0);
		float Blinn = pow(NdotH, MaterialShininess);
		specular = LightSpecularColor * MaterialSpecularColor * Blinn;
	}

	float attenuation = 1 / (1.0 +LightAttenuation.x * Ldist + LightAttenuation.y * pow(Ldist,2));

	vec4 reflectionColor = texture(u_cubemap,vec3(reflected.x,reflected.y,reflected.z)); //cor para meter no fragmento

	if(textured)
		colorOut = reflectionColor * vec4((ambient + (diffuse + specular) * attenuation),1.0); //se for um objecto com textura entao
		                                                                                       //a cor = textura+blinn phong
	else 
		colorOut = ex_Color * vec4((ambient + (diffuse + specular) * attenuation),1.0);
}
