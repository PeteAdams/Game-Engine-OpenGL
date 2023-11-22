#include "Model.h"

Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) 
	: subMeshes(std::vector<Mesh*>()), shaderProgram(0), modelInstances(std::vector<glm::mat4>())
{
	shaderProgram = shaderProgram_;
	
	obj = new LoadObjModel();
	obj->LoadModel(objPath_, matPath_);
	this->LoadModel();
}

Model::~Model()
{
	OnDestroy();
}

void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}

void Model::Render(Camera* camera_)
{
	for (auto m : subMeshes)
	{
		m->Render(camera_, modelInstances);
	}
}

void Model::OnDestroy()
{
	if (subMeshes.size() > 0)
	{
		for (Mesh* m : subMeshes)
		{
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}
	modelInstances.clear();
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(GetTrasform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = GetTrasform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(int index_) const
{
	return modelInstances[index_];
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}
	boundingbox = obj->GetBoundingBox();
	delete obj;
	obj = nullptr;
}

glm::mat4 Model::GetTrasform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;

	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);

	boundingbox.transform;

	return model;
}

BoundingBox Model::GetBoundingBox()
{
	return boundingbox;
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}