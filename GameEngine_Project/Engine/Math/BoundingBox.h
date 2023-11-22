#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox
{
	glm::vec3 minVert, maxVert;
	glm::mat4 transform;

	inline BoundingBox()
	{
		minVert = maxVert = glm::vec3();
		transform = glm::mat4();
	}
	inline BoundingBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::mat4 transform_)
	{
		minVert = minVert_;
		maxVert = maxVert_;
		transform = transform_;
	}
};

#endif