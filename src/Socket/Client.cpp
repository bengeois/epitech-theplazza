/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Client
*/

#include "Socket/Client.hpp"
#include "Error/Error.hpp"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

using namespace Plazza;

Client::Client(int fd, sockaddr_in &addr) : _fd(fd), _addr(addr), _read(true)
{
}

Client::Client(const std::string &addr, int port) : _fd(socket(AF_INET, SOCK_STREAM, 0)), _read(true)
{
    createClient(addr, port);
}

Client::Client(int port, const std::string &addr) : _fd(socket(AF_INET, SOCK_STREAM, 0)), _read(true)
{
    createClient(addr, port);
}

Client::~Client()
{
}

void Client::createClient(const std::string &addr, int port)
{
    if (_fd == -1)
        throw ClientError("Unable to create a socket", "Client");
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    if (connect(_fd, (sockaddr *)(&_addr), sizeof(_addr)) < 0)
        throw ClientError("Unable to connect to the client", "Client");
}

void Client::read()
{
    char buffer[1] = {0};
    int len;

    if ((len = ::read(_fd, buffer, 1)) == -1)
        throw ClientError("Fail to read data", "readClient");
    if (len == 0)
        return;
    std::cout << "{CLIENT} receive " << buffer[0] << std::endl;
    _data.push_back(buffer[0]);
}

void Client::write()
{
    std::cout << "{CLIENT} send " << _msg.front() << std::endl;
    if (::write(_fd, &_msg.front(), 1) == -1)
        throw ClientError("Fail write data", "writeClient");
    _msg.pop();
    if (_msg.empty()) {
        _write = false;
        _read = true;
    }
}

void Client::write(const std::string &msg)
{
    for (size_t i = 0; msg[i]; i++) {
        _msg.push(msg[i]);
    }
    _write = true;
    _read = false;
}

void Client::translateSelect(const fd_set &readfs, const fd_set &writefs)
{
    if (FD_ISSET(_fd, &writefs))
        write();
    if (FD_ISSET(_fd, &readfs))
        read();
}

void Client::setFdSet(fd_set *readfs, fd_set *writefs)
{
    if (_read)
        FD_SET(_fd, readfs);
    if (_write)
        FD_SET(_fd, writefs);
}

const std::string Client::getData()
{
    std::string data = "";
    size_t i = 0;

    for (; _data[i] && _data[i] != '\n'; i++);
    if (_data[i] != '\n')
        return (data);
    data = _data.substr(0, i);
    _data.erase(0, i + 1);
    data += "\n";
    return (data);
}

bool Client::isWriting() const
{
    return (_write);
}

bool Client::makeBlocking()
{
    int flags;

    flags = fcntl(_fd, F_GETFL, 0);
    if (flags == -1)
        return false;
    flags &= ~O_NONBLOCK;
    return fcntl(_fd, F_SETFL, flags) != 1;
}

bool Client::makeNonBlocking()
{
    int flags;

    flags = fcntl(_fd, F_GETFL, 0);
    if (flags == -1)
        return false;
    flags |= O_NONBLOCK;
    return fcntl(_fd, F_SETFL, flags) != 1;
}
