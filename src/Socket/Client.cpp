/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Client
*/

#include "Socket/Client.hpp"
#include "Error/Error.hpp"
#include <arpa/inet.h>

using namespace Plazza;

Client::Client(int fd, sockaddr_in &addr) : _fd(fd), _addr(addr)
{
}

Client::Client(const std::string &addr, int port) : _fd(socket(AF_INET, SOCK_STREAM, 0))
{
    if (_fd == -1)
        throw ClientError("Unable to create a socket", "Client");
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    if (connect(_fd, (sockaddr *)(&_addr), sizeof(_addr)) < 0)
        throw ClientError("Unable to connect to the client", "Client");
}

Client::~Client()
{
}

void Client::translateSelect(const fd_set &readfs, const fd_set &writefs)
{
    (void)readfs;
    (void)writefs;
}

void Client::setFdSet(fd_set *readfs, fd_set *writefs)
{
    (void)readfs;
    (void)writefs;
}