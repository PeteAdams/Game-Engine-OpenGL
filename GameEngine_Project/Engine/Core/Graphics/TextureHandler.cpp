#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;
std::map<std::string, Texture*> TextureHandler::textures = std::map<std::string, Texture*>();

TextureHandler::TextureHandler()
{
}

TextureHandler::~TextureHandler()
{
	//OnDestroy();
}

TextureHandler * TextureHandler::GetInstance()
{
	if (textureInstance.get() == nullptr)
	{
		textureInstance.reset(new TextureHandler);
	}
	return textureInstance.get();
}

void TextureHandler::OnDestroy()
{
	for (auto t : textures)
	{
		glDeleteTextures(1, &t.second->textureID);
		delete t.second;
		t.second = nullptr;
	}
	textures.clear();
}

void TextureHandler::CreateTexture(const std::string & textureName_, const std::string & textureFileName_)
{
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFileName_.c_str());

	if (!surface)
	{
		Debug::Error("Failed to load texture: " + textureName_, "TextureHandler.cpp", __LINE__);
		return;
	}
	t->width = static_cast<float>(surface->w);
	t->height = static_cast<float>(surface->h);

	//binds textures (creates surface)
	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);


	//Alternative if statement... before : is if, after : is else (can only use if setting a variable[mode])
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	//unbinding textures (prevents memory leak)
	glBindTexture(GL_TEXTURE_2D, 0);
	textures[textureName_] = t;
	SDL_FreeSurface(surface);
	surface = nullptr;
}

const GLuint TextureHandler::GetTexture(const std::string textureName_)
{
	if (textures.find(textureName_) != textures.end())
	{
		return textures[textureName_]->textureID;
	}
	return 0;
}

const Texture * TextureHandler::GetTextureData(const std::string & textureName_)
{
	if (textures.find(textureName_) != textures.end())
	{
		return textures[textureName_];
	}
	return nullptr;
}
