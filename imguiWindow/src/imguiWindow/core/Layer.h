#pragma once

#include <string>
#include "imguiWindow/events/Event.h"

class Layer
{
public:
	Layer(const std::string &name = "Layer") : m_debugname(name) {};
	virtual ~Layer() = default;

	virtual void on_attach() {};
	virtual void on_detach() {};
	virtual void on_update(float time) {};
	virtual void on_imgui_render() {};
	virtual void on_event(Event &event) {};

	const std::string& get_name() { return m_debugname; };
protected:
	std::string m_debugname;
};

