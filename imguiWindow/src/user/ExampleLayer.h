#pragma once
#include "core.h"

class ExampleLayer : public Layer
{
public:
	ExampleLayer();
	~ExampleLayer();

	void on_attach() override;
	void on_detach() override;

	void on_update() override;
	void on_imgui_render() override;

private:
	Framebuffer* m_framebuffer;
	
};

