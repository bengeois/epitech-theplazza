/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Server
*/

#include "Socket/Server.hpp"
#include "Error/Error.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <iostream>

using namespace Plazza;

Server::Server(int port) : _port(port), _fd(socket(AF_INET, SOCK_STREAM, 0))
{
    int tmp = 1;

    if (_fd == -1)
        throw ServerError("Unable to create a socket", "Server");
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int)) < 0)
        throw ServerError("Unable to set the fd of the server, try again", "Server");
    bindPort(_port);
    if (listen(_fd, 10) < 0)
        throw ServerError("Unable to listen ports", "Server");
}

int Server::getPort() const
{
    return (_port);
}

void Server::bindPort(int port)
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(_fd, (struct sockaddr *)(&_addr), sizeof(_addr)) < 0)
        throw ServerError("Unable to bind this port " + std::to_string(_port), "bindPort");
    socklen_t len = sizeof(_addr);
    getsockname(_fd, (sockaddr *)(&_addr), &len);
    _port = ntohs(_addr.sin_port);
}

int Server::newConnection()
{
    int fd = accept(_fd, nullptr, nullptr);

    if (_fd == -1)
        throw ServerError("Unable to connect with the client", "newConnection");
    return (fd);
}

int Server::getFd() const
{
    return (_fd);
}