#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource
{
private:
	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	glm::vec3 color;

public:
	LightSource();
	LightSource(glm::vec3 position_);
	LightSource(glm::vec3 position_, float diffuse_, float ambient_, glm::vec3 color_);
	~LightSource();

	void SetPosition(glm::vec3 position_);
	void SetAmbientValue(float ambientValue_);
	void SetDiffuseValue(float diffuseValue_);
	void SetColor(glm::vec3 color_);

	glm::vec3 GetPosition();
	float GetAmbientValue();
	float GetDiffuseValue();
	glm::vec3 GetColor();
};

#endif