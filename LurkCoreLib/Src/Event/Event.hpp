#pragma once
#include "EventArgs.hpp"
#include <functional>
#include <memory>  
#include <vector>

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

			int GetSubscribedFuncsLength();
			bool IsCallable();
			std::vector<EventFunc<EventArgsType>> GetFunc();
		private:
			std::vector<EventFunc<EventArgsType>> subscribedFuncs;
			void AddSubscriber(const EventFunc<EventArgsType> func);
		};

		template<class EventArgsType>
		Event<EventArgsType>::Event()
		{
		}

		template<class EventArgsType>
		inline void Event<EventArgsType>::Call(EventArgsType args)
		{
			for (auto& func : subscribedFuncs) {
				func(args);
			}
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
			subscribedFuncs.clear();
		}

		template<class EventArgsType>
		inline int Event<EventArgsType>::GetSubscribedFuncsLength()
		{
			return subscribedFuncs.size();
		}

		template<class EventArgsType>
		inline bool Event<EventArgsType>::IsCallable()
		{
			return GetSubscribedFuncsLength() != 0;
		}

		template<class EventArgsType>
		inline std::vector<EventFunc<EventArgsType>> Event<EventArgsType>::GetFunc()
		{
			return std::vector<EventFunc<EventArgsType>>(subscribedFuncs);
		}

		template<class EventArgsType>
		inline void Event<EventArgsType>::AddSubscriber(const EventFunc<EventArgsType> func)
		{
			subscribedFuncs.push_back(func);
		}

	}
}