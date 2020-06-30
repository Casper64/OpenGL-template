#include "pch.h"
#include "ImguiWindow/Application.h"

Application *Application::s_instance = nullptr;

Application::Application()
{
	s_instance = this;
	m_window = Window::Create();
	m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

	// init renderer

	m_imguiLayer = new ImguiLayer();
	push_overlay(m_imguiLayer);
}

Application::Application(WindowProps &props)
{
	s_instance = this;
	m_window = Window::Create(props);
	m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

	// init renderer

	m_imguiLayer = new ImguiLayer();
	push_overlay(m_imguiLayer);
}

Application::~Application()
{
	// shutdown renderer
}

void Application::onEvent(Event &e)
{
	std::cout << "from imguiWindow; " << e.toString() << std::endl;
	EventDispatcher dispatcher(e);
	
	for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it) {
		if (e.handled) break;
		(*it)->on_event(e);
	}
}

void Application::push_layer(Layer *layer)
{
	m_layerStack.push_layer(layer);
	layer->on_attach();
}

void Application::push_overlay(Layer *overlay)
{
	m_layerStack.push_overlay(overlay);
	overlay->on_attach();
}

void Application::close()
{
	m_running = false;
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
}

void Application::run()
{
	while (m_running && !glfwWindowShouldClose(m_window.get()->get_window())) {
		// initalize time variable
		float time = (float)glfwGetTime();
		
		for (Layer *layer : m_layerStack) {
			layer->on_update(time);
		}

		m_imguiLayer->begin();
		for (Layer *layer : m_layerStack) {
			layer->on_imgui_render();
		}
		m_imguiLayer->end();

		m_window->on_update();
	}
}
