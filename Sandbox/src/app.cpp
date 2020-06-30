#include "core.h"

#include "ExampleLayer.h"

class ImguiWindow : public Application
{
public:
	ImguiWindow()
	{
		push_layer(new ExampleLayer());
	}
	ImguiWindow(WindowProps &props)
		: Application(props)
	{
		push_layer(new ExampleLayer());
	}

	~ImguiWindow()
	{
	}

};

Application *create_application()
{
	WindowProps props("ImguiWindow", 1280, 720, true);
	return new ImguiWindow(props);
}
