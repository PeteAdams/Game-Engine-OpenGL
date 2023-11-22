#version 330 core

struct Light
{
	vec3 lightPos;
	float ambientValue;
	float diffuseValue;
	vec3 color;
};

struct Material
{
	sampler2D diffuseMap;
	float shininess; // Ns
	float transparency; //D

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

out vec4 color;

uniform Material material;
uniform Light light;
uniform vec3 cameraPos;

void main ()
{
vec3 ambient = light.ambientValue * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.color;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.lightPos - FragPosition);
float diff = max(dot(norm, lightDir), 0.0f);
vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.color;

vec3 viewDir = normalize(cameraPos - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
vec3 specular = (spec * material.specular) * light.color;

vec3 result = ambient + diffuse + specular;

color = vec4(result, material.transparency);
}