#include "pch.h"
#include "ExampleLayer.h"
#include "imgui.h"

#include <glad/glad.h>

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

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_framebuffer->unbind();
}

void ExampleLayer::on_imgui_render()
{
	static float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	ImGui::Begin("Imgui Window");
	ImGui::Text("This is a test window.");
	ImGui::ColorEdit4("Edit me!", color);
	ImGui::End();

	ImGui::Begin("Render window", nullptr, ImGuiWindowFlags_NoResize);

	uint32_t textureID = m_framebuffer->get_color_attachment_renderer_ID();
	ImGui::Image((void *)textureID, ImVec2{ 640, 360 });
	ImGui::End();
}
