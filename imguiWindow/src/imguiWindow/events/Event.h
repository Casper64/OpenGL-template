#pragma once
#include "pch.h"
#include "imguiWindow/base.h"

enum class EventType
{
	none = 0,
	keyPressed, keyReleased, keyTyped,
	mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled
};

enum EventCategory
{
	none = 0,
	eventCategoryInput = BIT(0),
	eventCategoryKeyboard = BIT(1),
	eventCategoryMouseButton = BIT(2),
	eventCategoryMouse = BIT(3)
};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

class Event
{
public:
	virtual ~Event() = default;
	bool handled = false;

	virtual EventType getEventType() const = 0;
	virtual const char *getName() const = 0;
	virtual int getCategoryFlags() const = 0;
	virtual std::string toString() const { return getName(); };

	bool isCategory(EventCategory category)
	{
		return getCategoryFlags() & category;
	}
};

class EventDispatcher
{
public:
	EventDispatcher(Event &event) : m_event(event) {};

	template<typename T, typename F>
	bool dispatch(const F &func)
	{
		if (m_event.getEventType() == T::GetStaticType()) {
			m_event.handled = func(static_cast<T &>(m_event));
			return true;
		}
		return false;
	}

private:
	Event &m_event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
	return os << e.toString();
}

