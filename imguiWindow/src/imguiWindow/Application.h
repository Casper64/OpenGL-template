#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "ImguiLayer.h"


int main(int argc, char **argv);

class Application
{
public:
	Application();
	Application(WindowData &props);
	virtual ~Application();

	void push_layer(Layer *layer);
	void push_overlay(Layer *overlay);

	Window &get_window() { return *m_window; };
	void close();

	static Application &get() { return *s_instance; };
	virtual void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
	void run();
private:
	std::unique_ptr<Window> m_window;
	ImguiLayer *m_imguiLayer;
	bool m_running = true;
	LayerStack m_layerStack;
private:
	static Application *s_instance;
	friend int ::main(int argc, char **argv);
};

Application *create_application();
