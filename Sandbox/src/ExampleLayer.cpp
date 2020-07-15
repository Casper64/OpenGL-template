#include "ExampleLayer.h"
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleLayer::ExampleLayer() 
	: Layer("ExampleLayer")
{
}

ExampleLayer::~ExampleLayer()
{
}

void ExampleLayer::on_attach()
{
	FramebufferSpecification specs;
	specs.Width = 640;
	specs.Height = 360;
	m_framebuffer = new Framebuffer(specs);
	m_checkerboardTexture = Texture2D::create("assets/textures/Checkerboard.png");
}

void ExampleLayer::on_detach()
{
}

void ExampleLayer::on_update(float time)
{
	static float rotation = 0.0f;
	static float oldTime = 0.0f;
	float dt;
	dt = time - oldTime;
	oldTime = time;
	// update shit 
	// ...

	Renderer::setClearColor(0, 0, 0, 0);
	Renderer::clear();

	m_framebuffer->bind();

	Renderer::setClearColor(m_clearColor);
	Renderer::clear();

	rotation += dt * 50.0f;

	Renderer2D::begin({ m_viewportSize[0], m_viewportSize[1] }, m_zoom);
	Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_checkerboardTexture, m_tilingFactor);
	Renderer2D::drawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, rotation, m_squareColor);
	Renderer2D::end();

	m_framebuffer->unbind();
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Imgui Window");
	ImGui::Text("This is a test window.");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_squareColor));
	ImGui::DragFloat("Tiling factor checkerboardTexture", &m_tilingFactor, 0.1f, 0.0f, 100.0f, "%.0f");
	ImGui::DragFloat("Zoom", &m_zoom, 0.02f, 0.0f, 5.0f, "%.3f");
	ImGui::End();

	//ImGui::SetNextWindowSize(ImVec2(640, 360 + 20));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Render window", nullptr);
	ImVec2 viewportContentSize = ImGui::GetContentRegionAvail();
	if (m_viewportSize[0] != viewportContentSize.x && m_viewportSize[1] != viewportContentSize.y) {
		m_framebuffer->resize((uint32_t)viewportContentSize.x, (uint32_t)viewportContentSize.y);
		m_viewportSize[0] = viewportContentSize.x;
		m_viewportSize[1] = viewportContentSize.y;
	}

	uint32_t textureID = m_framebuffer->get_color_attachment_renderer_ID();
	ImGui::Image((void *)textureID, ImVec2{ m_viewportSize[0], m_viewportSize[1] });
	ImGui::End();
	ImGui::PopStyleVar(1);
}

void ExampleLayer::on_event(Event &event)
{
}
