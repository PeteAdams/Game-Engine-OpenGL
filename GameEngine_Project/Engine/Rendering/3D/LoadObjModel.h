#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Core/FX/MaterialLoader.h"
#include "../../Math/BoundingBox.h"
#include "glm/gtx/string_cast.hpp"

#include <algorithm>
#include <sstream>

class LoadObjModel
{
public:

	LoadObjModel();
	~LoadObjModel();

	void LoadModel(const std::string& fileName_);
	void LoadModel(const std::string& fileName_, const std::string& matName_);
	void OnDestroy();

	std::vector<Vertex> GetVerts();
	std::vector<int> GetIndicies();
	std::vector<SubMesh> GetSubMeshes();
	
	BoundingBox GetBoundingBox();
private:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<int> indicies;
	std::vector<int> normalIndicies;
	std::vector<int> textureIndicies;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> meshes;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matName_);

	Material currentMaterial;

	BoundingBox boundingbox;
};

#endif