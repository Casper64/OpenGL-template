#pragma once
#include <glm/glm.hpp>

#include "imguiWindow/renderer/VertexArray.h"

class Renderer
{
public:
	static void setClearColor(glm::vec4 &color);
	static void setClearColor(float r, float g, float b, float a);
	static void clear();
	static void init();
	static void shutdown();

	static void drawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0);
};

