/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Socket
*/

#include "IPC/Socket.hpp"
#include "Error/Error.hpp"

using namespace Plazza;

Socket::Socket(int fd) : _fd(fd)
{
}

Socket::Socket() : _fd(socket(AF_INET, SOCK_STREAM, 0))
{
    if (_fd == -1)
        throw SocketError("Unable to create a socket", "Client");
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(1026);
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

    timeval time = {0, 100};

    while (1) {
        fd_set readfs;

        FD_ZERO(&readfs);
        FD_SET(_fd, &readfs);

        if (select(FD_SETSIZE, &readfs, NULL, NULL, &time) < 0)
            return (false);
        if (!FD_ISSET(_fd, &readfs))
            return (false);
        len = ::read(_fd, buffer, 1);
        if (len == 0) {
            _exist = false;
            return (false);
        }
        // std::cout << "{CLIENT} receive " << buffer[0] << std::endl;
        _data += buffer[0];
    }
    return (true);
}

const std::string Socket::getData()
{
    return (_data.getNextLine());
}

bool Socket::send()
{
    if (_msg.size() == 0)
        return (false);

    fd_set writefs;
    timeval time = {0, 100};

    FD_ZERO(&writefs);
    FD_SET(_fd, &writefs);

    if (select(FD_SETSIZE, NULL, &writefs, NULL, &time) < 0)
        return (false);
    if (!FD_ISSET(_fd, &writefs))
        return (true);

    const std::string data = _msg.getBuffer();
    int len = ::write(_fd, data.c_str(), data.size());

    if (len == -1)
        throw SocketError("Write fail", "Socket send");
    // std::cout << "{SERVER} write " + _msg.getBuffer() << std::endl;
    _msg.remove(len);
    return (true);
}

void Socket::send(const std::string &msg)
{
    _msg += msg;
}