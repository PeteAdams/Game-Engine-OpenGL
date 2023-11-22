#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "3D/GameObject.h"
#include "../Math/CollisionHandler.h"

#include <memory>

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();

	void AddGameObject(GameObject* gameObject_, std::string name_ = "");
	void AddModel(Model* model_);

	GameObject* GetGameObject(std::string name_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void OnDestroy();

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::map<std::string, GameObject*> sceneGameObjects;
	static std::map<GLuint, std::vector<Model*>> sceneModels;
};

#endif