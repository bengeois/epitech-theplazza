/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Socket
*/

#include "IPC/Socket.hpp"
#include "Error/Error.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace Plazza;

Socket::Socket() : _fd(socket(AF_INET, SOCK_STREAM, 0))
{
    if (_fd == -1)
        throw SocketError("Unable to create a socket", "Client");
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(1024);
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(_fd, (sockaddr *)(&_addr), sizeof(_addr)) < 0)
        throw SocketError("Unable to connect to the client", "Client");
}

Socket::~Socket()
{
    close(_fd);
}

bool Socket::read()
{
    char buffer[1] = {0};
    int len;

    while ((len = ::read(_fd, buffer, 1)) == -1) {
        if (len == 0) {
            _exist = false;
            return;
        }
        _data += buffer[0];
    }
    // std::cout << "{CLIENT} receive " << buffer[0] << std::endl;
}

const std::string Socket::getData()
{
    return (_data.getNextLine());
}

bool Socket::send()
{
    if (_msg.size() == 0)
        return (false);

    const std::string data = _msg.getBuffer();
    int len = ::write(_fd, data.c_str(), data.size());

    if (len == -1)
        throw SocketError("Write fail", "Socket send");
    _msg.remove(len);
    return (true);
}

void Socket::send(const std::string &msg)
{
    _msg += msg;
}