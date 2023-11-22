#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string file_)
{
	std::ifstream in(file_.c_str(), std::ios::in);

	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + file_, "LoadObjModel.cpp", __LINE__);
		return;
	}

	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(matName, m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
		}

		//Specular
		if (line.substr(0, 4) == "	Ns ") {
			std::istringstream v(line.substr(4));
			v >> m.shininess;
		}

		//Transparency
		if (line.substr(0, 3) == "	d ") {
			std::istringstream v(line.substr(3));
			v >> m.transparency;
		}

		//Ambient
		if (line.substr(0, 4) == "	Ka ") {
			std::istringstream v(line.substr(4));

			double x, y, z;

			v >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}

		//Diffuse
		if (line.substr(0, 4) == "	Kd ") {
			std::istringstream v(line.substr(4));

			double x, y, z;

			v >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}

		//Specular
		if (line.substr(0, 4) == "	Ks ") {
			std::istringstream v(line.substr(4));

			double x, y, z;

			v >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}

	}
	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(matName, m);
	}
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);

	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}