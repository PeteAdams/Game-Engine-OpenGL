#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window (nullptr), isRunning (false), fps(120), gameInterface(nullptr), currentScene(0), camera(nullptr)
{

}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_ ))
	{
		Debug::FatalError("Window failed to create", "CoreEngine.h", __LINE__);
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colorShader",
		"Engine/Core/Shaders/ColorVertexShader.glsl",
		"Engine/Core/Shaders/ColorFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Core/Shaders/VertexShader.glsl",
		"Engine/Core/Shaders/FragmentShader.glsl");

	if (gameInterface)
	{
		if (!gameInterface->OnCreate())
		//DEBUG STATEMENT HOMEWORK
		{
			Debug::FatalError("Game Interface failed to create", "CoreEngine.h", __LINE__);
			return isRunning = false;
		}
	}

	Debug::Info("Everything works", "CoreEngine.h", __LINE__);
	timer.Start();
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning)
	{
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning)
	{
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning()
{
	return isRunning;
}

void CoreEngine::SetIsRunning(bool isRunning_)
{
	isRunning = isRunning_;
}

CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

void CoreEngine::Update(const float deltaTime_)
{
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface)
	{
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete camera;
	camera = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	TextureHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	ShaderHandler::GetInstance()->OnDestroy();

	SDL_Quit();
	exit(0);
}

void CoreEngine::SetGameInterface(GameInterface *gameInterface_)
{
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int CurrentScene_)
{
	currentScene = CurrentScene_;
}

int CoreEngine::GetCurrentScene() const
{
	return currentScene;
}

glm::vec2 CoreEngine::GetScreenSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

void CoreEngine::NotifyOfMousePressed(int x_, int y_)
{

}
void CoreEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_)
{
	CollisionHandler::GetInstance()->Update(glm::vec2 (x_, y_), buttonType_);
}

void CoreEngine::NotifyOfMouseMove(int x_, int y_)
{
	if (camera)
	{
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera)
	{
		camera->ProcessMouseZoom(y_);
	}
}

void CoreEngine::ExitGame()
{
	isRunning = false;
}

void CoreEngine::SetCamera(Camera *camera_)
{
	camera = camera_;
}

Camera* CoreEngine::GetCamera()
{
	return camera;
}