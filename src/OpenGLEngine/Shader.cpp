#include <OpenGLEngine/Shader.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>

void OpenGLEngine::Shader::Load(std::string_view path, std::string& source)
{
	std::ifstream file;
	std::stringstream ss;

	try
	{
		file.open(path.data());
		ss << file.rdbuf();
		file.close();
		source = ss.str();
	}
	catch (std::exception e) {
		throw e;
	}
}

void OpenGLEngine::Shader::Compile(std::string sourceCode, const unsigned int shaderType, unsigned int& shader)
{
	int success;
	char infoLog[512];
	const char* sourceCStr = sourceCode.c_str();

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &sourceCStr, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::string msg(infoLog);
		msg.insert(0, "shader compilation error: ");
		throw std::runtime_error(msg.c_str());
	};

}

void OpenGLEngine::Shader::Link(std::vector<unsigned int> shaders)
{
	int success;
	char infoLog[512];

	this->m_shaderID = glCreateProgram();

	for (auto shader : shaders)
		glAttachShader(this->m_shaderID, shader);

	glLinkProgram(this->m_shaderID);

	glGetProgramiv(this->m_shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->m_shaderID, 512, NULL, infoLog);
		std::string msg(infoLog);
		msg.insert(0, "shader program link error: ");
		throw std::runtime_error(msg.c_str());
	};
}

OpenGLEngine::Shader::Shader()
{
}

OpenGLEngine::Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
{
	std::string vertexSource, fragmentSource;
	unsigned int vertexId, fragmentId;

	try {
		Load(vertexPath, vertexSource);
		Load(fragmentPath, fragmentSource);

		Compile(vertexSource, GL_VERTEX_SHADER, vertexId);
		Compile(fragmentSource, GL_FRAGMENT_SHADER, fragmentId);

		std::vector<unsigned int> shaders = { vertexId, fragmentId };
		Link(shaders);

		for (auto shader : shaders)
			glDeleteShader(shader);
	}
	catch (std::exception e) {
		throw e;
	}
}

void OpenGLEngine::Shader::Use()
{
	glUseProgram(m_shaderID);
}

unsigned int OpenGLEngine::Shader::ID()
{
	return this->m_shaderID;
}

OpenGLEngine::Shader::~Shader()
{
	glDeleteProgram(m_shaderID);
}

void OpenGLEngine::Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
}
void OpenGLEngine::Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}
void OpenGLEngine::Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderID, name.c_str()), value);
}
void OpenGLEngine::Shader::SetVec3(const std::string& name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(m_shaderID, name.c_str()), value1, value2, value3);
}
void OpenGLEngine::Shader::SetVec3(const std::string& name, glm::vec3 value) const
{
	SetVec3(name, value.x, value.y, value.z);
}
void OpenGLEngine::Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}