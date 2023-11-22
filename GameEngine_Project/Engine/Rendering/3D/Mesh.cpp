#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_)
	: VAO(0), VBO(0), shaderProgram(0)
{
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	OnDestroy();
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, normal)));

	//TEXTURE
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, texCoords)));

	//COLOR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, color)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");

	camPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambientValue");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.color");

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specLoc = glGetUniformLocation(shaderProgram, "material.specular");
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> &instances_)
{
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	//set materials after bind texture

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glm::vec3 copyCamPos = camera_->GetPosition();
	glm::vec3 copyLightPos = camera_->GetLightSource()[0]->GetPosition();
	glm::vec3 copyLightColor = camera_->GetLightSource()[0]->GetColor();

	glUniform3f(camPosLoc, copyCamPos.x, copyCamPos.y, copyCamPos.z);
	glUniform3f(lightPosLoc, copyLightPos.x, copyLightPos.y, copyLightPos.z);
	glUniform1f(lightAmbientLoc, camera_->GetLightSource()[0]->GetAmbientValue());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSource()[0]->GetDiffuseValue());
	glUniform3f(lightColorLoc, copyLightColor.x, copyLightColor.y, copyLightColor.z);

	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);
	glUniform3f(ambientLoc, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLoc, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specLoc, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);

	glBindVertexArray(VAO);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::OnDestroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	subMesh.vertexList.clear();
	subMesh.meshIndicies.clear();
}