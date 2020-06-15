#include "pch.h"
#include "core.h"

#include "ExampleLayer.h"

class ImguiWindow : public Application
{
public:
	ImguiWindow()
	{
		push_layer(new ExampleLayer());
	}

	~ImguiWindow()
	{
	}
};

Application *create_application()
{
	return new ImguiWindow();
}
