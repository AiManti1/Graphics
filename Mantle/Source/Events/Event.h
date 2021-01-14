#pragma once
#include "mtlpch.h"
#include "Macros.h"

// TODO: Buffered-events bus for later processing during the "event" part of the update stage not to
// block the Engine, as now events occur and get immediately dispatched.


/*	This is the main event system file: with it, the engine knows what happens.	*/

// All events data (window->data) will be stemmed down from Event.h system (MEngine events, WindowEvents, KeyPressed, MouseMoved etc.).
// They will be dispatched as events to Layers, which listen to OnUpdate(), OnTick() etc. and handle it there.


namespace mtl 
{
	// Implemented in Window64 class via callback functions.
	enum class EventType
	{
		None = 0,
		WindowFocus, WindowLostFocus, WindowMoved, WindowResize, WindowClose, 	// Engine's Events
		MtlTick, MtlUpdate, MtlRender,
		KeyPressed, KeyReleased, KeyTyped,										// Keyboard Events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,		// Mouse Events
		JoystickConnected, JoystickDisconnected									// Joystick Events
	};

// 'static EventType GetStaticType()' is used to check event type at runtime.
// Virtual is needed for polimorphic usage: to reference to Event base class to check Event's type (with Event Dispatcher case).
#define EVENT_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; } 	

	// Base class for events.
	class MTL Event
	{
	public:		 
		/**
			@brief	Marker not to let an handled event be propagated down further thelayers.
					If a button on the screen is clicked (so this event has been handled,),
					the layer underneath it (like game world) does not receive this click event,
					since it has been handled by the button.
			@type	bool
		*/
		bool m_Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0; // for debugging
		virtual std::string ToString() const { return GetName(); } 
	};

	/* NOTE:
	MEngine creates a Window. Window gets events and message them back to 'MEngine'. Window and Engine should not be tied!
	MEngine receives events from 'Window-class' and dispatches them to a 'Layer'.
	A window receives a callback function and constructs MEngine-event and message it back to MEngine.

	Dispatcher automatically casts events to the appropriate function (so events can have custom parameters).
	(Making a big switch statement and cast each one repeatedly is not efficient.)
		
	If every layer needs input, we get tons of methods.
	*/

	/*
	Another idea is to have one class called "Input" that handles almost every event. 
	Maybe the better idea would be to create those methods in the base layer class and do not touch them in derived classes.﻿	
	*/
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}
	private:
		Event& m_Event;

		// Т is any type of event(resize etc.). To be implemented in a class, where this event is being handled.
		// With it, we'll provide a window with the possibility of callback.
		// We receive a kind of Event. Then instantiate the class 'EventDispatcher' with the Event we have received (Event& event). 
		// Then we call the function 'bool Dispatch(EventFn<T> func)' with another Event-function (EventFn<T> func).
		// OnEvent dispatched automatically to f.e.: OnMouseMoved(MouseMovedEvent* e)
		template<typename T>
		using EventFn = std::function<bool(T&)>; 
	public:
		/* NOTE:
		bool Dispatch(EventFn<T> func) checks which Event Type [.GetEventType()] is the current Event [m_Event.],
		that we're trying to dispatch by 'EventFn = std::function<bool(T&)>',
		whether or not it matches the type 'T' of function 'std::function<bool(T&)'.
		If it does, we'll call that function with that Event [func(*(T*)&m_Event)].
		Since it is a static function [T::GetStaticType()] we can take [T::] and get its static type.
		There is no type safety here [EventFn<T> func to make sure it is an Event]
		*/
		/**
			@brief	Dispatcher propagates events down the layers to the certain layer (to block other layers).
			@type	bool
			@arg	EventFn<T> func [using EventFn = std::function<bool(T&)>;]
			@return bool [m_Handled].
		*/
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	};

	// For Logging Library, that looks for this operator, to show the name of the event occured.
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	/*
		inline std::ostream& operator<<(std::ostream& os, const glm::mat4& e)
	{
		return os << e.ToString();
	}
	*/
}
