#pragma once
#include "pch.h"
#include "imguiWindow/core/base.h"

enum class ShaderDataType
{
	None = 0, Float, vec2, vec3, vec4, mat2, mat3, mat4, Int, Bool
};

static uint32_t shaderDataTypeSize(ShaderDataType type)
{
	switch (type) {
	case ShaderDataType::Float:    return 4;
	case ShaderDataType::vec2:   return 4 * 2;
	case ShaderDataType::vec3:   return 4 * 3;
	case ShaderDataType::vec4:   return 4 * 4;
	case ShaderDataType::mat2:     return 4 * 2 * 2;
	case ShaderDataType::mat3:     return 4 * 3 * 3;
	case ShaderDataType::mat4:     return 4 * 4 * 4;
	case ShaderDataType::Int:      return 4;
	case ShaderDataType::Bool:     return 1;
	}
	return 0;
}

struct BufferElement
{
	std::string name;
	ShaderDataType type;
	uint32_t size;
	size_t offset;
	bool normalized;

	BufferElement() = default;

	BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
		: name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized)
	{
	}

	uint32_t getComponentCount() const
	{
		switch (type) {
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::vec2:  return 2;
		case ShaderDataType::vec3:  return 3;
		case ShaderDataType::vec4:  return 4;
		case ShaderDataType::mat2:    return 2; // 2* vec2
		case ShaderDataType::mat3:    return 3; // 3* vec3
		case ShaderDataType::mat4:    return 4; // 4* vec4
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Bool:    return 1;
		}
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout() {}

	BufferLayout(const std::initializer_list<BufferElement> &elements)
		: m_elements(elements)
	{
		calculateOffsetsAndStride();
	}

	uint32_t getStride() const { return m_stride; }
	const std::vector<BufferElement> &getElements() const { return m_elements; }

	std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
private:
	void calculateOffsetsAndStride()
	{
		size_t offset = 0;
		m_stride = 0;
		for (auto &element : m_elements) {
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}
private:
	std::vector<BufferElement> m_elements;
	uint32_t m_stride = 0;
};

class VertexBuffer
{
public:
	VertexBuffer(uint32_t size);
	VertexBuffer(float *vertices, uint32_t size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

	void setData(const void *data, uint32_t size) ;

	const BufferLayout &getLayout() const;
	void setLayout(const BufferLayout &layout);

	static Ref<VertexBuffer> create(uint32_t size);
	static Ref<VertexBuffer> create(float *vertices, uint32_t size);
private:
	uint32_t m_renderID;
	BufferLayout m_layout;
};

// Currently Hazel only supports 32-bit index buffers
class IndexBuffer
{
public:
	IndexBuffer(uint32_t *indices, uint32_t count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	uint32_t getCount() const;

	static Ref<IndexBuffer> create(uint32_t *indices, uint32_t count);
private:
	uint32_t m_renderID;
	uint32_t m_count;
};