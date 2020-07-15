#include "pch.h"
#include "imguiWindow/renderer/Renderer.h"
#include "imguiWindow/renderer/Renderer2D.h"

#include <glad/glad.h>

void Renderer::setClearColor(glm::vec4 &color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char *message,
	const void *userParam)
{
	printf("opengl error: %s\n", message);

}

void Renderer::init()
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	Renderer2D::init();
}

void Renderer::shutdown()
{
	Renderer2D::shutdown();
}

void Renderer::drawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount)
{
	uint32_t count = indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
