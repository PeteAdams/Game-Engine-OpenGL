#ifndef MESH_H
#define MESH_H

#include "../../Core/Camera/Camera.h"
#include "../../Core/Graphics/MaterialHandler.h"

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 color;
};

struct SubMesh
{
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndicies;
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4> &instances_);
	void OnDestroy();

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint diffuseMapLoc, shininessLoc, transparencyLoc, ambientLoc, diffuseLoc, specLoc;
	SubMesh subMesh;
	GLuint camPosLoc;
	GLuint lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColorLoc;
};

#endif