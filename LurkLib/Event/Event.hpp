#pragma once
#include "EventArgs.hpp"
#include <functional>

namespace Lurk {
	namespace Event {

		template<typename EventType, typename ArgType>
		using EventFunc = std::function<void(EventArgs<EventType, ArgType>)>;


		template<typename EventType, typename ArgType>
		class Event
		{
		public:
			Event<EventType, ArgType>();

			void Call(EventArgs<EventType, ArgType>);

			Event<EventType, ArgType>& operator+=(const EventFunc<EventType, ArgType>);
			void Subscribe(const EventFunc<EventType, ArgType>);

			void UnSubscribe();

			EventFunc<EventType, ArgType> GetFunc();
		private:
			EventFunc<EventType, ArgType> subscribedFunc;
			void AddSubscriber(const EventFunc<EventType, ArgType> func);
		};

		template<typename EventType, typename ArgType>
		Event<EventType, ArgType>::Event()
		{
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::Call(EventArgs<EventType, ArgType> args)
		{
			subscribedFunc(args);
		}

		template<typename EventType, typename ArgType>
		inline Event<EventType, ArgType>& Event<EventType, ArgType>::operator+=(const EventFunc<EventType, ArgType> func)
		{
			AddSubscriber(func);
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::Subscribe(const EventFunc<EventType, ArgType> func)
		{
			AddSubscriber(func);
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::UnSubscribe()
		{
			subscribedFunc = 0;
		}

		template<typename EventType, typename ArgType>
		inline EventFunc<EventType, ArgType> Event<EventType, ArgType>::GetFunc()
		{
			return subscribedFunc;
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::AddSubscriber(const EventFunc<EventType, ArgType> func)
		{
			subscribedFunc = func;
		}

	}
}