#pragma once

namespace Lurk{
    namespace Network{
        enum class TcpExceptions{
            NoException = 0,
            SocketCreationError = 1,
            InvalidAddress = 2,
            ConnectionError = 3,
            BindError = 4,
            ListenError = 5,
            AcceptError = 6
        };
    }
    
}

