#pragma once

#include <string>
#include "imguiWindow/core/base.h"

#include <glad/glad.h>

class Texture
{
public:
	virtual ~Texture() = default;

	virtual uint32_t getWidth() const = 0;
	virtual uint32_t getHeight() const = 0;
	virtual uint32_t getRendererID() const = 0;

	virtual void setData(void *data, uint32_t size) = 0;

	virtual void bind(uint32_t slot = 0) const = 0;
	
	virtual bool operator == (const Texture &other) const = 0;
};

class Texture2D : public Texture
{
public:
	Texture2D(uint32_t width, uint32_t height);
	Texture2D(const std::string &path);
	~Texture2D();

	virtual uint32_t getWidth() const override { return m_width; }
	virtual uint32_t getHeight() const override { return m_height; }
	virtual uint32_t getRendererID() const override { return m_rendererID; }

	virtual void setData(void *data, uint32_t size) override;

	virtual void bind(uint32_t slot = 0) const override;

	virtual bool operator == (const Texture &other) const override
	{
		return m_rendererID == ((Texture2D&)other).m_rendererID;
	}

	static Ref<Texture2D> create(uint32_t width, uint32_t height);
	static Ref<Texture2D> create(const std::string &path);

private:
	std::string m_path;
	uint32_t m_width, m_height;
	uint32_t m_rendererID;
	GLenum m_internalFormat, m_dataFormat;
};

