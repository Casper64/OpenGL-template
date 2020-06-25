#include "core.h"

#include "ExampleLayer.h"

class ImguiWindow : public Application
{
public:
	ImguiWindow()
	{
		push_layer(new ExampleLayer());
	}
	ImguiWindow(WindowData &props)
		: Application(props)
	{
		push_layer(new ExampleLayer());
	}

	~ImguiWindow()
	{
	}

	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override
	{
		std::cout << key << std::endl;
	}
};

Application *create_application()
{
	WindowData props("ImguiWindow", 1280, 720, true);
	return new ImguiWindow(props);
}
