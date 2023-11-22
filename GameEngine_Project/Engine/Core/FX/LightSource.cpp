#include "LightSource.h"

LightSource::LightSource() :
	position(glm::vec3(0.3f, 0.3f, 1.0f)),
	diffuseValue(1.0f),
	ambientValue(1.0f),
	color(glm::vec3(0.7f, 0.7f, 0.7f))
{
}

LightSource::LightSource(glm::vec3 position_) :
	diffuseValue(1.0f),
	ambientValue(1.0f),
	color(glm::vec3(1.0f, 1.0f, 1.0f))
{
	position = position_;
}

LightSource::LightSource(glm::vec3 position_, float diffuse_, float ambient_, glm::vec3 color_)
{
	position = position_;
	color = color_;
	diffuseValue = diffuse_;
	ambientValue = ambient_;
}
LightSource::~LightSource()
{
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbientValue(float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuseValue(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

void LightSource::SetColor(glm::vec3 color_)
{
	color = color_;
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}

float LightSource::GetAmbientValue()
{
	return ambientValue;
}

float LightSource::GetDiffuseValue()
{
	return diffuseValue;
}

glm::vec3 LightSource::GetColor()
{
	return color;
}