#pragma once
#include "imguiWindow/events/Event.h"


class KeyEvent : public Event
{
public:
	int getKeyCode() const { return m_keyCode; };

	EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
protected:
	KeyEvent(int keyCode) : m_keyCode(keyCode) {};
	int m_keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_repeatCount(repeatCount) {};

	int getRepeatCount() const { return m_repeatCount; };

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyPRessedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(keyPressed);

private:
	int m_repeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode) : KeyEvent(keycode) {};

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(keyReleased);
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(int keycode) : KeyEvent(keycode) {};

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(keyTyped);
};

