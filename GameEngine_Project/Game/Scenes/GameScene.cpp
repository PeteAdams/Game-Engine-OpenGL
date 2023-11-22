#include "GameScene.h"

GameScene::GameScene() : Scene()
{

}

GameScene::~GameScene()
{
	OnDestroy();
}

bool GameScene::OnCreate() 
{
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLightSources(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 1.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate();

	Model* diceModel = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl",
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(diceModel);

	Model* appleModel = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl",
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-3.0f, -1.0f, 0.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel), "Apple");

	SceneGraph::GetInstance()->GetGameObject("Apple")->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));

	return true;
}

void GameScene::Update(const float deltaTime_) 
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render() 
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void GameScene::OnDestroy() 
{
}