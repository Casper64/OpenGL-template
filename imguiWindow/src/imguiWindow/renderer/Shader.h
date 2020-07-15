#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "imguiWindow/core/base.h"

typedef unsigned int GLenum;

class Shader
{
public:
	Shader(const std::string &filePath);
	Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
	~Shader();

	void bind() const;
	void unBind() const;

	void setInt(const std::string &name, int value);
	void setIntArray(const std::string &name, int *values, uint32_t count);
	void setFloat(const std::string &name, float value);
	void setVec2(const std::string &name, glm::vec2 &value);
	void setVec3(const std::string &name, glm::vec3 &value);
	void setVec4(const std::string &name, glm::vec4 &value);
	void setMat2(const std::string &name, glm::mat2 &value);
	void setMat3(const std::string &name, glm::mat3 &value);
	void setMat4(const std::string &name, glm::mat4 &value);

	const std::string &getName() const { return m_name; };
	
	void setUniformBool(const std::string &name, bool value);
	void setUniformInt(const std::string &name, int value);
	void setUniformIntArray(const std::string &name, int *values, uint32_t count);
	void setUniformFloat(const std::string &name, float value);
	void setUniformVec2(const std::string &name, glm::vec2 &value);
	void setUniformVec3(const std::string &name, glm::vec3 &value);
	void setUniformVec4(const std::string &name, glm::vec4 &value);
	void setUniformMat2(const std::string &name, glm::mat2 &value);
	void setUniformMat3(const std::string &name, glm::mat3 &value);
	void setUniformMat4(const std::string &name, glm::mat4 &value);
	
	// TODO: different filePaths for vertex and fragment shader
	static Ref<Shader> create(const std::string &filePath);
	static Ref<Shader> create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
private:
	std::string readFile(const std::string &filePath);
	std::unordered_map < GLenum, std::string> preProcess(const std::string &source);
	void compile(const std::unordered_map<GLenum, std::string> &shaderSources);
private:
	uint32_t m_renderID;
	std::string m_name;
};

