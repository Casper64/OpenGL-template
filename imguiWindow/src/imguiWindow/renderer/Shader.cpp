#include "pch.h"
#include "imguiWindow/renderer/Shader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>


static GLenum ShaderTypeFromString(const std::string &type)
{
	if (type == "vertex") {
		return GL_VERTEX_SHADER;
	}
	else if (type == "fragment") {
		return GL_FRAGMENT_SHADER;
	}
	else {
		return 0;
	}
}

Shader::Shader(const std::string &filePath)
{
	std::string source = readFile(filePath);
	auto shaderSources = preProcess(source);
	compile(shaderSources);

	// extract name from filepath
	auto lastSlash = filePath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = filePath.rfind('.');
	auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
	m_name = filePath.substr(lastSlash, count);
}

Shader::Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
	: m_name(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;
	compile(sources);
}

Shader::~Shader()
{
	glDeleteProgram(m_renderID);
}

void Shader::bind() const
{
	glUseProgram(m_renderID);
}

void Shader::unBind() const
{
	glUseProgram(0);
}

void Shader::setInt(const std::string &name, int value)
{
	setUniformInt(name, value);
}

void Shader::setIntArray(const std::string &name, int *values, uint32_t count)
{
	setUniformIntArray(name, values, count);
}

void Shader::setFloat(const std::string &name, float value)
{
	setUniformFloat(name, value);
}

void Shader::setVec2(const std::string &name, glm::vec2 &value)
{
	setUniformVec2(name, value);
}

void Shader::setVec3(const std::string &name, glm::vec3 &value)
{
	setUniformVec3(name, value);

}

void Shader::setVec4(const std::string &name, glm::vec4 &value)
{
	setUniformVec4(name, value);

}

void Shader::setMat2(const std::string &name, glm::mat2 &value)
{
	setUniformMat2(name, value);
}

void Shader::setMat3(const std::string &name, glm::mat3 &value)
{
	setUniformMat3(name, value);
}

void Shader::setMat4(const std::string &name, glm::mat4 &value)
{
	setUniformMat4(name, value);
}

void Shader::setUniformBool(const std::string &name, bool value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform1i(location, value);
}

void Shader::setUniformInt(const std::string &name, int value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform1i(location, value);
}

void Shader::setUniformIntArray(const std::string &name, int *values, uint32_t count)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform1iv(location, count, values);
}

void Shader::setUniformFloat(const std::string &name, float value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform1f(location, value);
}

void Shader::setUniformVec2(const std::string &name, glm::vec2 &value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void Shader::setUniformVec3(const std::string &name, glm::vec3 &value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniformVec4(const std::string &name, glm::vec4 &value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniformMat2(const std::string &name, glm::mat2 &value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniformMat3(const std::string &name, glm::mat3 &value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniformMat4(const std::string &name, glm::mat4 &value)
{
	GLint location = glGetUniformLocation(m_renderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

Ref<Shader> Shader::create(const std::string &filePath)
{
	return CreateRef<Shader>(filePath); 
}

Ref<Shader> Shader::create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
{
	return CreateScope<Shader>(name, vertexSrc, fragmentSrc);
}

std::string Shader::readFile(const std::string &filePath)
{
	std::string result;
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	if (in) {
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1) {
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
			in.close();
		}
		else {
			printf("Could not read from file %s\n", filePath.c_str());
		}
	}
	else {
		printf("Could not open file %s\n", filePath.c_str());
	}
	return result;
}

std::unordered_map<GLenum, std::string> Shader::preProcess(const std::string &source)
{
	std::unordered_map<GLenum, std::string> shaderSources;

	const char *typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
	while (pos != std::string::npos) {
		size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
		if (eol == std::string::npos) printf("Syntax error!\n");
		size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
		std::string type = source.substr(begin, eol - begin);
		if (ShaderTypeFromString(type) == 0) printf("Invalid Shader type!\n");

		size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
		if (nextLinePos == std::string::npos) printf("Syntax error!\n");
		pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

		shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
	}

	return shaderSources;
}

void Shader::compile(const std::unordered_map<GLenum, std::string> &shaderSources)
{
	GLuint program = glCreateProgram();
	std::array<GLenum, 2> glShaderIDs;
	int glShaderIDIndex = 0;
	for (auto &kv : shaderSources) {
		GLenum type = kv.first;
		const std::string &source = kv.second;

		GLuint shader = glCreateShader(type);

		const GLchar *sourceCstr = source.c_str();
		glShaderSource(shader, 1, &sourceCstr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			printf("%s", infoLog.data());
			printf("Shader compilation failure\n");
			break;
		}
		glAttachShader(program, shader);
		glShaderIDs[glShaderIDIndex++] = shader;
	}

	m_renderID = program;

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);

		for (auto id : glShaderIDs) {
			glDeleteShader(id);
		}

		printf("%s", infoLog.data());
		printf("Shader link failure\n");
		return;
	}
	for (auto id : glShaderIDs) {
		glDetachShader(program, id);
		glDeleteShader(id);
	}

}
