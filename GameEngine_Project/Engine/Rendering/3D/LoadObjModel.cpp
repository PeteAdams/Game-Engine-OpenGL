#include "LoadObjModel.h"

LoadObjModel::LoadObjModel() : currentMaterial(Material()) //initialize remaining privates
{
}

LoadObjModel::~LoadObjModel()
{
	OnDestroy();
}

void LoadObjModel::LoadModel(const std::string & fileName_)
{
	std::ifstream in(fileName_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot load obj file " + fileName_, "LoadObjModel.cpp", __LINE__);
		return;
	}
	std::string line;
	boundingbox.maxVert = glm::vec3(FLT_MIN);
	boundingbox.minVert = glm::vec3(FLT_MAX);
	while (std::getline(in, line))
	{
		//VERTEX DATA
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			double x, y, z;
			v >> x; v >> y; v >> z;
			vert = glm::vec3(x, y, z);

			if (vert.x < boundingbox.minVert.x) boundingbox.minVert.x = vert.x;
			if (vert.y < boundingbox.minVert.y) boundingbox.minVert.y = vert.y;
			if (vert.z < boundingbox.minVert.z) boundingbox.minVert.z = vert.z;

			if (vert.x > boundingbox.maxVert.x) boundingbox.maxVert.x = vert.x;
			if (vert.y > boundingbox.maxVert.y) boundingbox.maxVert.y = vert.y;
			if (vert.z > boundingbox.maxVert.z) boundingbox.maxVert.z = vert.z;

			vertices.push_back(vert);

		}
		//NORMAL DATA
		if (line.substr(0, 3) == "vn ")
		{
			std::istringstream vn(line.substr(3));
			glm::vec3 norm;
			double x, y, z;
			vn >> x >> y >> z;
			norm = glm::vec3(x, y, z);
			normals.push_back(norm);
		}
		//TEXTURE COORDINATE DATA
		else if (line.substr(0, 3) == "vt ")
		{
			std::istringstream vt(line.substr(3));
			glm::vec2 text;
			double x, y, z;
			vt >> x >> y >> z;
			text = glm::vec2(x, y);
			textureCoords.push_back(text);
		}
		//FACE DATA
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream f(line.substr(2));

			int v, t, n;
			char slash;

			for (int i = 0; i < 3; i++) {
				f >> v >> slash >> t >> slash >> n;

				indicies.push_back(v - 1);
				textureIndicies.push_back(t - 1);
				normalIndicies.push_back(n - 1);
			}
		}
		//NEW MATERIAL (new mesh)
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indicies.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadObjModel::LoadModel(const std::string & fileName_, const std::string & matName_)
{
	LoadMaterialLibrary(matName_);
	LoadModel(fileName_);
}

void LoadObjModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indicies.clear();
	normalIndicies.clear();
	textureIndicies.clear();
	meshVertices.clear();
	meshes.clear();
}

std::vector<Vertex> LoadObjModel::GetVerts()
{
	return meshVertices;
}

std::vector<int> LoadObjModel::GetIndicies()
{
	return indicies;
}

std::vector<SubMesh> LoadObjModel::GetSubMeshes()
{
	return meshes;
}

void LoadObjModel::PostProcessing()
{
	for (int i = 0; i < indicies.size(); i++)
	{
		Vertex vert;

		vert.position = vertices[indicies[i]];
		vert.normal = normals[normalIndicies[i]];
		vert.texCoords = textureCoords[textureIndicies[i]];

		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndicies = indicies;
	mesh.material = currentMaterial;
	meshes.push_back(mesh);

	indicies.clear();
	normalIndicies.clear();
	textureIndicies.clear();
	meshVertices.clear();
	currentMaterial = Material();
}

void LoadObjModel::LoadMaterial(const std::string & fileName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadObjModel::LoadMaterialLibrary(const std::string & matName_)
{
	MaterialLoader::LoadMaterial(matName_);
}

BoundingBox LoadObjModel::GetBoundingBox()
{
	return boundingbox;
}