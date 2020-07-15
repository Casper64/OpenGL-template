#include "pch.h"
#include "imguiWindow/renderer/VertexArray.h"

#include <glad/glad.h>

static GLenum ShaderDatatypeToBasetype(ShaderDataType type)
{
	switch (type) {
	case ShaderDataType::Float:    return GL_FLOAT;
	case ShaderDataType::vec2:   return GL_FLOAT;
	case ShaderDataType::vec3:   return GL_FLOAT;
	case ShaderDataType::vec4:   return GL_FLOAT;
	case ShaderDataType::mat2:     return GL_FLOAT;
	case ShaderDataType::mat3:     return GL_FLOAT;
	case ShaderDataType::mat4:     return GL_FLOAT;
	case ShaderDataType::Int:      return GL_INT;
	case ShaderDataType::Bool:     return GL_BOOL;
	}
	return 0;
}

VertexArray::VertexArray()
{
	

	glCreateVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
	

	glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::bind() const
{
	

	glBindVertexArray(m_rendererID);
}

void VertexArray::unbind() const
{
	

	glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
{
	

	

	glBindVertexArray(m_rendererID);
	vertexBuffer->bind();

	const auto &layout = vertexBuffer->getLayout();
	for (const auto &element : layout) {
		switch (element.type) {
		case ShaderDataType::Float:
		case ShaderDataType::vec2:
		case ShaderDataType::vec3:
		case ShaderDataType::vec4:
		case ShaderDataType::Int:
		case ShaderDataType::Bool:
		{
			glEnableVertexAttribArray(m_vertexBufferIndex);
			glVertexAttribPointer(m_vertexBufferIndex,
								  element.getComponentCount(),
								  ShaderDatatypeToBasetype(element.type),
								  element.normalized ? GL_TRUE : GL_FALSE,
								  layout.getStride(),
								  (const void *)element.offset);
			m_vertexBufferIndex++;
			break;
		}
		case ShaderDataType::mat3:
		case ShaderDataType::mat4:
		{
			uint8_t count = element.getComponentCount();
			for (uint8_t i = 0; i < count; i++) {
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribPointer(m_vertexBufferIndex,
									  count,
									  ShaderDatatypeToBasetype(element.type),
									  element.normalized ? GL_TRUE : GL_FALSE,
									  layout.getStride(),
									  (const void *)(sizeof(float) * count * i));
				glVertexAttribDivisor(m_vertexBufferIndex, 1);
				m_vertexBufferIndex++;
			}
			break;
		}
		}
	}

	m_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
{
	glBindVertexArray(m_rendererID);
	indexBuffer->bind();

	m_indexBuffer = indexBuffer;
}

Ref<VertexArray> VertexArray::create()
{
	return CreateRef<VertexArray>();
}
