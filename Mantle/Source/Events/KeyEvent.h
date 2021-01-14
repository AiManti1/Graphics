#pragma once
#include "Events/Event.h"

namespace mtl {

	class MTL KeyEvent : public Event
	{
	protected:
		int m_KeyCode;
	public:
		inline int GetKeyCode() const { return m_KeyCode; } // we don't need to set it, since that happens when the Event gets constrcuted.
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
	};

	class MTL KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		/* NOTE:
		The macro is used instead of this (defined in Event.h):
		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KeyPressed"; }
		*/
			EVENT_TYPE(KeyPressed)
	};

	class MTL KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_TYPE(KeyReleased)
	};

	class MTL KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_TYPE(KeyTyped)
	};
}
