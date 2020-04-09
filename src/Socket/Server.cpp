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

using namespace Plazza;

Server::Server(int port) : _port(port), _fd(socket(AF_INET, SOCK_STREAM, 0))
{
    int tmp = 1;

    if (_fd == -1)
        throw ServerError("Unable to create a socket", "Server");
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int)) < 0)
        throw ServerError("Unable to set the fd of the server, try again", "Server");
    if (_port != -1)
        bindPort(_port);
    else
        bindPort();
    if (listen(_fd, 10) < 0)
        throw ServerError("Unable to listen ports", "Server");
}

Server::~Server()
{
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
}

void Server::bindPort()
{
    for (size_t i = 1; i < 65536; i++) {
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(i);
        _addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(_fd, (struct sockaddr *)(&_addr), sizeof(_addr)) < 0)
            continue;
        _port = i;
        return;
    }
    throw ServerError("Unable to found a free port, try again after a few moment", "bindPort");
}

void Server::newConnection()
{
    sockaddr_in client;
    socklen_t len = sizeof(client);
    int fd = accept(_fd, (sockaddr *)(&client), &len);

    if (_fd == -1)
        throw ServerError("Unable to connect with the client", "newConnection");
    _clients.push_back(std::make_unique<Client>(fd, client));
}

void Server::translateSelect(const fd_set &readfs, const fd_set &writefs)
{
    if (FD_ISSET(_fd, &readfs))
        newConnection();
    std::for_each(_clients.begin(), _clients.end(), [&readfs, &writefs](const std::unique_ptr<Client> &client) {
        client->translateSelect(readfs, writefs);
    });
}

void Server::setFdSet(fd_set *readfs, fd_set *writefs)
{
    FD_SET(_fd, readfs);
    std::for_each(_clients.begin(), _clients.end(), [&readfs, &writefs](const std::unique_ptr<Client> &client) {
        client->setFdSet(readfs, writefs);
    });
}