#pragma once

#include <string>

class Layer
{
public:
	Layer(const std::string &name = "Layer") : m_debugname(name) {};
	virtual ~Layer() = default;

	virtual void on_attach() {};
	virtual void on_detach() {};
	virtual void on_update() {};
	virtual void on_imgui_render() {};

	const std::string& get_name() { return m_debugname; };
protected:
	std::string m_debugname;
};

