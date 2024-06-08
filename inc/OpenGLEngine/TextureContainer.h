#pragma once

#include <OpenGLEngine/Texture.h>

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

namespace OpenGLEngine {

	class TextureContainer : public std::vector<Texture>
	{
	private:
		void Load(std::pair<std::string, textureType> imagePath);
	public:
		TextureContainer();
		TextureContainer(std::map<std::string, textureType> textures);
		TextureContainer(std::string_view diffusePath, std::string_view specularPath = "", std::string_view normalPath = "", std::string_view heightPath = "");
		std::vector<unsigned int> GetIDs(textureType typeEnum);
		std::string GetPath();
		std::size_t Size();
	};
}