#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <stdexcept>

namespace OpenGLEngine {

	class Shader
	{
	private:
		unsigned int m_shaderID;

		void Load(std::string_view path, std::string& source);
		void Compile(std::string sourceCode, const unsigned int shaderType, unsigned int& shader);
		void Link(std::vector<unsigned int> shaders);

	public:
		Shader();
		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		~Shader();
		void Use();

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec3(const std::string& name, float value1, float value2, float value3) const;
		void SetVec3(const std::string& name, glm::vec3 value) const;
		void SetMat4(const std::string& name, glm::mat4 value) const;

		unsigned int ID();

	};

}