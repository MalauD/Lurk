#pragma once
#include "./../EventArgs.hpp"
#include "ServerEventTypes.hpp"

namespace Lurk {
    namespace Event{
        template<typename ArgType>
        class ServerEventArgs : public EventArgs<ServerEventTypes, ArgType> {
        public:
            ServerEventArgs(ServerEventTypes SEventType, ArgType);
        };

        template<typename ArgType>
        ServerEventArgs<ArgType>::ServerEventArgs(ServerEventTypes SEventType, ArgType il) {
            this->SetType(SEventType);
            this->SetArg(il);
        }

    }
}


