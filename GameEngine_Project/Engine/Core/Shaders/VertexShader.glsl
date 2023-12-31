#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec4 color;

out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
Normal = mat3(inverse(transpose(model))) * normal;

TexCoords = texCoords;

FragPosition = vec3(model * vec4(position, 1.0f));

gl_Position = proj * view * model * vec4(position, 1.0f);
}