#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr)
	{
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::AddGameObject(GameObject* gameObject_, std::string name_)
{
	if (name_ == "")
	{
		std::string newName = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newName);
		sceneGameObjects[newName] = gameObject_;
	}

	else if (sceneGameObjects.find(name_) == sceneGameObjects.end())
	{
		gameObject_->SetTag(name_);
		sceneGameObjects[name_] = gameObject_;
	}

	else
	{
		Debug::Error("Trying to add a game object with the name " + name_ + "that already exists", "SceneGraph.cpp", __LINE__);

		std::string newName = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newName);
		sceneGameObjects[newName] = gameObject_;
	}
	CollisionHandler::GetInstance()->AddObject(gameObject_);
}

void SceneGraph::AddModel(Model* model_)
{
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end())
	{
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), std::vector<Model*>{model_}));
	}
	else
	{
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

GameObject* SceneGraph::GetGameObject(std::string name_)
{
	if (sceneGameObjects.find(name_) != sceneGameObjects.end())
	{
		return sceneGameObjects[name_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects)
	{
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_)
{
	for (auto entry : sceneModels)
	{
		glUseProgram(entry.first);

		for (auto m : entry.second)
		{
			m->Render(camera_);
		}
	}
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0)
	{
		for (auto go : sceneGameObjects)
		{
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0)
	{
		for(auto entry : sceneModels)
			if (entry.second.size() > 0)
			{
				for (auto m : entry.second)
				{
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		sceneModels.clear();
	}
}