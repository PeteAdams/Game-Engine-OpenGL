#include "Window.h"

Window::Window()
{
	window = nullptr;
	width = 0;
	height = 0;
}

Window::~Window()
{
	onDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Debug::FatalError("Window failed to create", "Window.h", __LINE__);
		return false;
	}
	width = width_;
	height = height_;
	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width_,
		height_,
		SDL_WINDOW_OPENGL);
	if (!window)
	{
		Debug::FatalError("Graphics failed to render", "Window.h", __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetAttributes();
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		Debug::Error ("Failed to initialize glewInt", "Window.h", __LINE__);
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	Debug::Info("Everything works", "Window.h", __LINE__);

	return true;
}

void Window::onDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const 
{
	return width;
}

int Window::GetHeight() const 
{
	return height;
}

SDL_Window *Window::GetWindow() const 
{
	return window;
}

void Window::SetAttributes() 
{
	glewExperimental = GL_TRUE;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetSwapInterval(1);
}