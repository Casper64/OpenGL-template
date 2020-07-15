#include "pch.h"
#include "imguiWindow/core/Window.h"


#include "imguiWindow/core/Application.h"

#include "imguiWindow/events/Event.h"
#include "imguiWindow/events/KeyEvent.h"
#include "imguiWindow/events/MouseEvent.h"

#define STB_IMAGE_IMPLEMENTATION
#include "imguiWindow/dependencies/stb_image.h"


static void glfwErrorCallback(int error, const char *description)
{
	printf("GLFW error (%d): %s\n", error, description);
}

Window::Window(const WindowProps &props)
{
	init(props);
}


Window::~Window()
{
}


Scope<Window> Window::Create(const WindowProps &props)
{
	return CreateScope<Window>(props);
}

void Window::init(const WindowProps &data)
{
	m_data.width = data.width;
	m_data.height = data.height;
	m_data.title = data.title;
	strcpy_s(m_data.icon, data.icon);

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

	glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_PRESS:
		{
			KeyPressedEvent event(static_cast<int>(key), 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(static_cast<int>(key));
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(static_cast<int>(key), 1);
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int keycode) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(static_cast<int>(keycode));
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(static_cast<int>(button));
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(static_cast<int>(button));
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	});


	if (m_data.icon[0] != '\0') {
		GLFWimage *icon = new GLFWimage();
		//stbi_set_flip_vertically_on_load(true);
		icon->pixels = stbi_load("icon.png", &icon->width, &icon->height, 0, 4);
		glfwSetWindowIcon(m_window, 1, icon);
		stbi_image_free(icon->pixels);
		delete icon;
	}
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

