#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_);
	GameObject(Model* model_, glm::vec3 position_);
	~GameObject();

	//Getters
	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox() const;
	std::string GetTag() const;
	bool GetHit() const;

	//Setters
	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);
	
	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void OnDestroy();

private:
	glm::vec3 position, rotation, scale;
	float angle;
	int modelInstance;

	Model* model;
	
	BoundingBox boundingbox;
	std::string tag;

	bool hit;
};

#endif