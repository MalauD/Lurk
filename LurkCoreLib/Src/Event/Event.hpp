#pragma once
#include "EventArgs.hpp"
#include <functional>
#include <memory>  

namespace Lurk {
	namespace Event {

		class EventArgs;

		template<class EventArgsClass>
		using EventFunc = std::function<void(EventArgsClass)>;


		template<class EventArgsType>
		class Event
		{
			static_assert(std::is_base_of<EventArgs, EventArgsType>::value, "EventArgsType must derive from EventArgs");

		public:

			Event();

			void Call(EventArgsType);

			Event& operator+=(const EventFunc<EventArgsType>);
			void Subscribe(const EventFunc<EventArgsType>);

			void UnSubscribe();

			EventFunc<EventArgsType> GetFunc();
		private:
			EventFunc<EventArgsType> subscribedFunc;
			void AddSubscriber(const EventFunc<EventArgsType> func);
		};

		template<class EventArgsType>
		Event<EventArgsType>::Event()
		{
		}

		template<class EventArgsType>
		inline void Event<EventArgsType>::Call(EventArgsType args)
		{
			subscribedFunc(args);
		}


		template<class EventArgsType>
		[[deprecated("Replace with Subscribe(const EventFunc<EventArgsType>)")]] inline Event<EventArgsType>& Event<EventArgsType>::operator+=(const EventFunc<EventArgsType> func)
		{
			AddSubscriber(func);
			return *this;
		}

		template<class EventArgsType>
		inline void Event<EventArgsType>::Subscribe(const EventFunc<EventArgsType> func)
		{
			AddSubscriber(func);
		}

		template<class EventArgsType>
		inline void Event<EventArgsType>::UnSubscribe()
		{
			subscribedFunc = 0;
		}

		template<class EventArgsType>
		inline EventFunc<EventArgsType> Event<EventArgsType>::GetFunc()
		{
			return subscribedFunc;
		}

		template<class EventArgsType>
		inline void Event<EventArgsType>::AddSubscriber(const EventFunc<EventArgsType> func)
		{
			subscribedFunc = func;
		}

	}
}