#pragma once
#include "pch.h"
#include "imguiWindow/core/base.h"
#include "imguiWindow/OpenGL/OpenGLContext.h"
#include "imguiWindow/events/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct WindowProps
{
	std::string title;
	unsigned int width;
	unsigned int height;
	bool vsync;
	char icon[512] = "";

	WindowProps(const std::string &title = "Imgui Window", unsigned int width = 1280, unsigned int height = 720, bool vsync = true)
		: title(title), width(width), height(height), vsync(vsync)
	{
	}

};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event &)>;

	Window(const WindowProps &props);
	~Window();

	void on_update();
	unsigned int get_width() const { return m_data.width; };
	unsigned int get_height() const { return m_data.height; };

	void setEventCallback(const EventCallbackFn &callback) { m_data.EventCallback = callback; };
	void setVSync(bool enabled);
	bool isVSync();

	GLFWwindow* get_window() const { return m_window; };
	GLFWmonitor *get_monitor() const { return m_monitor; };
	void get_monitor_size(int &width, int &height)
	{
		const GLFWvidmode *mode = glfwGetVideoMode(m_monitor);
		width = mode->width;
		height = mode->height;
	};
	void get_cursor_pos(double *x, double *y)
	{
		glfwGetCursorPos(m_window, x, y);
	}
	void get_window_pos(int *x, int *y)
	{
		glfwGetWindowPos(m_window, x, y);
	}

	static Scope<Window> Create(const WindowProps &props = WindowProps());
private:
	void init(const WindowProps &data);
	void shutdown();
	

private:
	GLFWwindow *m_window;
	GLFWmonitor *m_monitor;
	Scope<OpenGLContext> m_context;

	struct WindowData
	{
		std::string title;
		unsigned int width, height;
		bool vsync;
		char icon[512] = "";
		EventCallbackFn EventCallback;
	};

	WindowData m_data;
};

