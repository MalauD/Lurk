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
			void Call(EventArgs<EventType, ArgType>);

			Event<EventType, ArgType>& operator+=(const EventFunc&);
			void Subscribe(const EventFunc&);

			void UnSubscribe();
		private:
			EventFunc& subscribedFunc;
			void AddSubscriber(EventFunc& func);
		};

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::Call(EventArgs<EventType, ArgType> args)
		{
			subscribedFunc(args);
		}

		template<typename EventType, typename ArgType>
		inline Event<EventType, ArgType>& Event<EventType, ArgType>::operator+=(const EventFunc<EventType, ArgType>& func)
		{
			AddSubscriber(func);
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::Subscribe(const EventFunc<EventType, ArgType>& func)
		{
			AddSubscriber(func);
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::UnSubscribe()
		{
			subscribedFunc = 0;
		}

		template<typename EventType, typename ArgType>
		inline void Event<EventType, ArgType>::AddSubscriber(EventFunc<EventType, ArgType>& func)
		{
			subscribedFunc = func;
		}

	}
}