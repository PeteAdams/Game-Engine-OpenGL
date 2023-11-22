#include "CollisionHandler.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr)
	{
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate()
{
	prevCollisions.clear();
	colliders.clear();
}

void CollisionHandler::AddObject(GameObject* gameObject_)
{
	colliders.push_back(gameObject_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition_, CoreEngine::GetInstance()->GetScreenSize(),
		CoreEngine::GetInstance()->GetCamera());

	GameObject* hitResult = nullptr;
	float shortestDist = FLT_MAX;

	for (auto go : colliders)
	{
		if (mouseRay.IsColliding(&go->GetBoundingBox()))
		{
			if (mouseRay.intersectionDistance < shortestDist)
			{
				hitResult = go;
				shortestDist = mouseRay.intersectionDistance;
			}
		}
	}

	if (hitResult)
	{
		hitResult->SetHit(true, buttonType_);
	}

	for (auto prev : prevCollisions)
	{
		if (hitResult != prev && prev != nullptr)
		{
			prev->SetHit(false, buttonType_);
			prev = nullptr;
		}
	}
	prevCollisions.clear();

	if (hitResult)
	{
		prevCollisions.push_back(hitResult);
	}
}

void CollisionHandler::OnDestroy()
{
	for (auto go : colliders)
	{
		go = nullptr;
	}
	colliders.clear();

	for (auto go : prevCollisions)
	{
		go = nullptr;
	}
	prevCollisions.clear();
}