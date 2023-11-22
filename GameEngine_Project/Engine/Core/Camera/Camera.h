#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../FX/LightSource.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);
	glm::vec3 GetPosition();
	glm::mat4 GetView() const;
	const glm::mat4 GetPerspective();
	const glm::mat4 GetOrthographic();

	void ProcessMouseMovement(float xOffset_, float yOffset_);
	void ProcessMouseZoom(int y_);

	void AddLightSources(LightSource* light_);
	std::vector<LightSource*> GetLightSource();

	void OnDestroy();

	glm::vec2 GetClippingPlanes() const;
private:
	void UpdateCameraVectors();

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float yaw, pitch;
	float fieldOfView;
	float nearPlane, farPlane;
	glm::vec3 forwardVector, upVector, rightVector, worldUp;

	std::vector<LightSource*> lightSources;
};

#endif