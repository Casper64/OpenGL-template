#pragma once
#include "ImguiWindow/Layer.h"

class ImguiLayer : public Layer
{
public:
	ImguiLayer();
	~ImguiLayer() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;

	void begin();
	void end();
private:
	float m_time = 0.0f;
};

