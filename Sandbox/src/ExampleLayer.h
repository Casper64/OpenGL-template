#pragma once
#include "core.h"
#include "imguiWindow/renderer/include.h"


class ExampleLayer : public Layer
{
public:
	ExampleLayer();
	~ExampleLayer();

	void on_attach() override;
	void on_detach() override;

	void on_update(float time) override;
	void on_imgui_render() override;

	void on_event(Event &event);

private:
	Framebuffer* m_framebuffer;
	float m_viewportSize[2] = { 0.0f, 0.0f };
	Ref<Texture2D> m_checkerboardTexture;
	glm::vec4 m_clearColor = { 0, 0, 0, 0 };
	glm::vec4 m_squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	float m_tilingFactor = 10.0f;
	float m_zoom = 1.0f;
	
};

