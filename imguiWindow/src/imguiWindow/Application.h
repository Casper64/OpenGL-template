#pragma once
#include "pch.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

typedef void (*MainLoop)(void);

struct WindowProps
{
	std::string title;
	unsigned int width;
	unsigned int height;
	bool vsync;

	WindowProps(const std::string &title = "Imgui Window", unsigned int width = 1280, unsigned int height = 720, bool vsync = true)
		: title(title), width(width), height(height), vsync(vsync)
	{
	}
};

class Application
{
public:
	Application();
	Application(WindowProps &props);
	~Application();
	unsigned int get_width() { return m_props.width; };
	unsigned int get_height() { return m_props.height; };
	void set_vsync(bool enabled);
	void is_vsync(bool enabled);
	GLFWwindow *get_window() { return m_window; };
	void run();
	void set_main_loop(MainLoop callback);

private:
	int init();
	MainLoop render_callback;
private:
	WindowProps m_props;
	GLFWwindow *m_window;
	bool m_running = true;
	ImGuiIO io;
};

