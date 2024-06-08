#include <OpenGLEngine/TextureContainer.h>

void OpenGLEngine::TextureContainer::Load(std::pair<std::string, textureType> imagePath)
{
	Texture texture(imagePath.first);
	texture.TextureType = imagePath.second;

	this->push_back(texture);
}

OpenGLEngine::TextureContainer::TextureContainer() {}

OpenGLEngine::TextureContainer::TextureContainer(std::map<std::string, textureType> textures) {

	for (std::pair kvp : textures) {
		Load(kvp);
	}

}

OpenGLEngine::TextureContainer::TextureContainer(std::string_view diffusePath, std::string_view specularPath, std::string_view normalPath, std::string_view heightPath)
{
	std::pair<std::string, textureType> kvp = { diffusePath.data(), textureTypeDiffuse };
	Load(kvp);
	kvp = { specularPath.data(), textureTypeSpecular };
	Load(kvp);
	kvp = { normalPath.data(), textureTypeNormal };
	Load(kvp);
	kvp = { heightPath.data(), textureTypeHeight };
	Load(kvp);
}

std::vector<unsigned int> OpenGLEngine::TextureContainer::GetIDs(textureType typeEnum)
{
	std::vector<unsigned int> returnVector;

	for (auto& texture : *this) {
		if (texture.TextureType == typeEnum)
			returnVector.push_back(texture.ID);
	}

	return returnVector;
}

std::string OpenGLEngine::TextureContainer::GetPath()
{
	return std::string();
}

std::size_t OpenGLEngine::TextureContainer::Size()
{
	return this->size();
}
