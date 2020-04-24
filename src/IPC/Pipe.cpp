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
    if (pipe(_parentPipe) < 0 || pipe(_childPipe) < 0)
        throw PipeError("Pipe failed", "Pipe");
}

Pipe::~Pipe()
{
    close(_parentPipe[0]);
    close(_parentPipe[1]);
    close(_childPipe[0]);
    close(_childPipe[1]);
}

bool Pipe::read()
{
    timeval time = {0, 100};
    char buffer[256 + 1] = {0};
    fd_set readfs;
    int len;

    FD_ZERO(&readfs);
    FD_SET(getFd(true), &readfs); // A changer

    if (select(FD_SETSIZE, &readfs, NULL, NULL, &time) < 0)
        return false;
    if (!FD_ISSET(getFd(true), &readfs)) // A changer
        return false;
    len = ::read(getFd(true), buffer, 256); // A Changer
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

    timeval time = {0, 1000};
    fd_set writefs;

    FD_ZERO(&writefs);
    FD_SET(getFd(false), &writefs); // A changer

    if (select(FD_SETSIZE, NULL, &writefs, NULL, &time) < 0)
        return false;
    if (!FD_ISSET(getFd(false), &writefs)) // A changer
        return true;

    const std::string data = _sending.getBuffer();
    int len = ::write(getFd(false), data.c_str(), data.size()); // A changer

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

void Pipe::setRelation(Relation relation)
{
    _relation = relation;
    if (_relation == CHILD) {
        close(_parentPipe[1]);
        close(_childPipe[0]);
    } else {
        close(_parentPipe[0]);
        close(_childPipe[1]);
    }
}

IIPC::Relation Pipe::getRelation() const
{
    return (_relation);
}

int Pipe::getFd(bool read) const
{
    if (_relation == CHILD) {
        if (read)
            return (_parentPipe[0]);
        return (_childPipe[1]);
    }
    if (read)
        return (_childPipe[0]);
    return (_parentPipe[1]);
}