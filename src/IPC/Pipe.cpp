/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pipe
*/

#include "IPC/Pipe.hpp"
#include "Error/Error.hpp"
#include <unistd.h>

using namespace Plazza;

Pipe::Pipe() : _exist(true)
{
    if (pipe(_writePipe) < 0 || pipe(_readPipe) < 0)
        throw PipeError("Pipe failed", "Pipe");
}

Pipe::~Pipe()
{
    close(_writePipe[0]);
    close(_writePipe[1]);
    close(_readPipe[0]);
    close(_readPipe[1]);
}

bool Pipe::read()
{
    timeval time = {0, 100};
    char buffer[256 + 1] = {0};
    fd_set readfs;
    int len;

    FD_ZERO(&readfs);
    FD_SET(_readPipe[0], &readfs); // A changer

    if (select(FD_SETSIZE, &readfs, NULL, NULL, &time) < 0)
        return false;
    if (!FD_ISSET(_readPipe[0], &readfs)) // A changer
        return false;
    len = ::read(_readPipe[0], buffer, 256); // A Changer
    if (len == 0) {
        _exist = false;
        return false;
    }
    _received += buffer;
    return true;
}

const std::string Pipe::getData()
{
    return _received.getNextLine();
}

bool Pipe::send()
{
    if (_sending.size() == 0)
        return false;

    timeval time = {0, 100};
    fd_set writefs;

    FD_ZERO(&writefs);
    FD_SET(_writePipe[0], &writefs); // A changer

    if (select(FD_SETSIZE, NULL, &writefs, NULL, &time) < 0)
        return false;
    if (!FD_ISSET(_writePipe[0], &writefs)) // A changer
        return true;

    const std::string data = _sending.getBuffer();
    int len = ::write(_writePipe[0], data.c_str(), data.size()); // A changer

    if (len == -1)
        throw SocketError("Write fail", "Socket send");
    // std::cout << "{SERVER} write " + _msg.getBuffer() << std::endl;
    _sending.remove(len);
    return true;
}

void Pipe::send(const std::string &msg)
{
    _sending.operator+=(msg);
}

bool Pipe::exist() const
{
    return _exist;
}