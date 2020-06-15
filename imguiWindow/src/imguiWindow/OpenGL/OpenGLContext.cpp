#include "pch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLContext::OpenGLContext(GLFWwindow *window_handle)
	: m_window_handle(window_handle)
{
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(m_window_handle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	printf("version: %d.%d", versionMajor, versionMinor);
}

void OpenGLContext::swap_buffers()
{
	glfwSwapBuffers(m_window_handle);
}



Scope<OpenGLContext> OpenGLContext::create(void *window)
{
	return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
}
