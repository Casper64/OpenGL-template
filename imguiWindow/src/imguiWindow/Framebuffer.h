#pragma once

struct FramebufferSpecification
{
	FramebufferSpecification(uint32_t width, uint32_t height) : Width(width), Height(height) {};
	FramebufferSpecification(): Width(0), Height(0) {};
	uint32_t Width, Height;
	// FramebufferFormat Format = 
	uint32_t Samples = 1;
	bool SwapChainTarget = false;
};

class Framebuffer
{
public:
	Framebuffer(const FramebufferSpecification &spec);
	~Framebuffer();

	void invalidate();
	void bind();
	void unbind();
	void resize(uint32_t width, uint32_t height);

	uint32_t get_color_attachment_renderer_ID() { return m_ColorAttachment; };

private:
	uint32_t m_RendererID;
	uint32_t m_ColorAttachment, m_DepthAttachment;
	FramebufferSpecification m_Specification;
};

