#include "pch.h"
#include "ExampleLayer.h"
#include "imgui.h"

#include <glad/glad.h>

static float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

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
}

void ExampleLayer::on_detach()
{
}

void ExampleLayer::on_update()
{
	// update shit 
	// ...

	m_framebuffer->bind();

	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	m_framebuffer->unbind();
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Imgui Window");
	ImGui::Text("This is a test window.");
	ImGui::ColorEdit4("Edit me!", clearColor);
	ImGui::End();

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
}
