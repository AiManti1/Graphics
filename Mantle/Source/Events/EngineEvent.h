#pragma once
#include "Events/Event.h"

namespace mtl 
{
	
	class MTL WindowResizeEvent : public Event
	{
	private:
		unsigned int m_Width, m_Height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EVENT_TYPE(WindowResize)	
	};

	class MTL WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		EVENT_TYPE(WindowClose)
	};

	class MTL MtlTickEvent : public Event
	{
	public:
		MtlTickEvent() {}
		EVENT_TYPE(MtlTick)
	};

	class MTL MtlUpdateEvent : public Event
	{
	public:
		MtlUpdateEvent() {}
		EVENT_TYPE(MtlUpdate)
	};

	class MTL MtlRenderEvent : public Event
	{
	public:
		MtlRenderEvent() {}
		EVENT_TYPE(MtlRender)
	};
}
