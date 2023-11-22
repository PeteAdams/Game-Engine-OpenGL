#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Core/Graphics/ShaderHandler.h"
#include "Camera/Camera.h"
#include "../Core/Graphics/TextureHandler.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"

#include <memory>

class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
	void SetIsRunning(bool isRunning_);
	void SetGameInterface(GameInterface *gameInterface_);
	void SetCurrentScene(int CurrentScene_);
	int GetCurrentScene() const;

	static CoreEngine* GetInstance();
	glm::vec2 GetScreenSize() const;

	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);

	void ExitGame();

	void SetCamera(Camera *camera_);
	Camera* GetCamera();
private:
	CoreEngine();
	~CoreEngine();

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Window* window;
	Timer timer;
	GameInterface *gameInterface;
	Camera *camera;

	bool isRunning;
	unsigned int fps;
	int currentScene;
};

#endif