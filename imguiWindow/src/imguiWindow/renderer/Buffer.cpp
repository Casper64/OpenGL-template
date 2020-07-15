#include "pch.h"

#include "imguiWindow/renderer/Buffer.h"
#include "imguiWindow/renderer/Renderer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &m_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float *vertices, uint32_t size)
{
	glCreateBuffers(1, &m_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_renderID);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(const void *data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

const BufferLayout &VertexBuffer::getLayout() const
{
	return m_layout;
}

void VertexBuffer::setLayout(const BufferLayout &layout)
{
	m_layout = layout;
}

Ref<VertexBuffer> VertexBuffer::create(uint32_t size)
{
	return CreateRef<VertexBuffer>(size);
}

Ref<VertexBuffer> VertexBuffer::create(float *vertices, uint32_t size)
{
	return CreateRef<VertexBuffer>(vertices, size);
}




IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count)
	: m_count(count)
{
	glCreateBuffers(1, &m_renderID);
	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_renderID);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::getCount() const
{
	return m_count;
}

Ref<IndexBuffer> IndexBuffer::create(uint32_t *indices, uint32_t count)
{
	return CreateRef<IndexBuffer>(indices, count);
}
