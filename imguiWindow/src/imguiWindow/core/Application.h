#pragma once

#include "imguiWindow/core/Window.h"
#include "imguiWindow/core/LayerStack.h"
#include "imguiWindow/core/ImguiLayer.h"
#include "imguiWindow/events/Event.h"


int main(int argc, char **argv);

class Application
{
public:
	Application();
	Application(WindowProps &props);
	virtual ~Application();

	void onEvent(Event &e);

	void push_layer(Layer *layer);
	void push_overlay(Layer *overlay);

	Window &get_window() { return *m_window; };
	void close();

	static Application &get() { return *s_instance; };

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
