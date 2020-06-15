#include "pch.h"
#include "Window.h"

static void glfwErrorCallback(int error, const char *description)
{
	printf("GLFW error (%d): %s\n", error, description);
}

Window::Window(const WindowData &props)
{
	init(props);
}


Window::~Window()
{
}


Scope<Window> Window::Create(const WindowData &props)
{
	return CreateScope<Window>(props);
}

void Window::init(const WindowData &data)
{
	m_data.width = data.width;
	m_data.height = data.height;
	m_data.title = data.title;

	int success = glfwInit();
	if (!success) {
		printf("Failed to initialize GLFW!\n");
	}
	glfwSetErrorCallback(glfwErrorCallback);

	m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);

	// create context?
	m_context = OpenGLContext::create(m_window);
	m_context->init();

	glfwSetWindowUserPointer(m_window, &m_data);
	setVSync(true);

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
		WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		// do callbacks
	});
}

void Window::shutdown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::on_update()
{
	glfwPollEvents();
	m_context->swap_buffers();
}

void Window::setVSync(bool enabled)
{
	if (enabled) {
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
	m_data.vsync = enabled;
}

bool Window::isVSync()
{
	return m_data.vsync;
}

