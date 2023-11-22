#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
int MouseEventListener::mouseX = 0; 
int MouseEventListener::mouseY = 0;
int MouseEventListener::prevMouseX = 0;
int MouseEventListener::prevMouseY = 0;
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	switch (e_.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		UpdateMousePositon();
		NotifyOfMousePressed(e_.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdateMousePositon();
		NotifyOfMouseReleased(e_.button.button);
		break;
	case SDL_MOUSEMOTION:
		UpdateMousePositon();
		NotifyOfMouseMove();
		break;
	case SDL_MOUSEWHEEL:
		NotifyOfMouseScroll(e_.wheel.y);
		break;
	default:
		break;
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMousePressed(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseReleased(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove()
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseMove(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if(engineInstance)
	{
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return glm::vec2(prevMouseX, prevMouseY);
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return glm::vec2(mouseX, mouseY);
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouseX - prevMouseX, prevMouseY - mouseY);
}

void MouseEventListener::UpdateMousePositon()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);

	tempY = engineInstance->GetScreenSize().y - tempY;
	
	if (firstUpdate)
	{
		prevMouseX = mouseX = tempX;
		prevMouseY = mouseY = tempY;
		//always make sure you reset to false if first update is only true once.
		firstUpdate = false;
	}
	else if (tempX != mouseX || tempY != mouseY)
	{
		prevMouseX = mouseX;
		prevMouseY = mouseY;
		mouseX = tempX;
		mouseY = tempY;
	}
}
