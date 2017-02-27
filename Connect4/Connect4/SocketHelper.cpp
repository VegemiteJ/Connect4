#include "SocketHelper.h"

ServerSocketSet connection;

void Init(std::string port)
{
    connection = ServerSocketSet(port);
}
