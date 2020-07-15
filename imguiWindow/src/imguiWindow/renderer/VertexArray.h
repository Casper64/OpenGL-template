#pragma once

#include <memory>
#include "imguiWindow/renderer/Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer);
	void setIndexBuffer(const Ref<IndexBuffer> &indexbuffer);

	const std::vector<Ref<VertexBuffer>> &getVertexBuffers() const { return m_vertexBuffers; };
	const Ref<IndexBuffer> &getIndexBuffer() const { return m_indexBuffer; };

	static Ref<VertexArray> create();
private:
	uint32_t m_rendererID;
	uint32_t m_vertexBufferIndex = 0;
	std::vector<Ref<VertexBuffer>> m_vertexBuffers;
	Ref<IndexBuffer> m_indexBuffer;
};

