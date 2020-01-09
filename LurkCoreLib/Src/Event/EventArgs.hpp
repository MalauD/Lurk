#pragma once

namespace Lurk {
    namespace Event {
        template<typename EventType, typename ArgType>
        class EventArgs {
        protected:
            void SetType(EventType);
            void SetArg(ArgType);
        public:
            ArgType GetArg();
            EventType GetType();
        private:
            EventType Type;
            ArgType Arg;
        };


        template<typename EventType, typename ArgType>
        void EventArgs<EventType, ArgType>::SetType(EventType et) {
            Type = et;
        }

        template<typename EventType, typename ArgType>
        void EventArgs<EventType, ArgType>::SetArg(ArgType il) {
            Arg = il;
        }

        template<typename EventType, typename ArgType>
        EventType EventArgs<EventType, ArgType>::GetType() {
            return Type;
        }

        template<typename EventType, typename ArgType>
        ArgType EventArgs<EventType, ArgType>::GetArg() {
            return Arg;
        }

    }
}