#pragma once
#include "imguiWindow/core/base.h"

struct GLFWwindow;

class OpenGLContext
{
public:
	OpenGLContext(GLFWwindow *window_handle);

	void init();
	void swap_buffers();

	static Scope<OpenGLContext> create(void *window);

private:
	GLFWwindow *m_window_handle;
};

