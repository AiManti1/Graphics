#pragma once
#include "Event.h"

namespace mtl {

	class MTL JoystickConnectedEvent : public Event
	{
	private:
		unsigned int m_Joystick;
	public:
		JoystickConnectedEvent(unsigned int joystick)
			: m_Joystick(joystick) {}

		inline unsigned int GetJoystick() const { return m_Joystick; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JoystickConnectedEvent: " << m_Joystick;
			return ss.str();
		}

		EVENT_TYPE(JoystickConnected)
	};

	class MTL JoystickDisconnectedEvent : public Event
	{
	private:
		unsigned int m_Joystick;
	public:
		JoystickDisconnectedEvent(unsigned int joystick)
			: m_Joystick(joystick) {}

		inline unsigned int GetJoystick() const { return m_Joystick; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JoystickDisconnectedEvent: " << m_Joystick;
			return ss.str();
		}

		EVENT_TYPE(JoystickDisconnected)
	};
}
