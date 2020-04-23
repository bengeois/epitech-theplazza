/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <iostream>
#include <strings.h>
#include "UserShell/UserShell.hpp"

using namespace Plazza;

UserShell::UserShell() : _readFds(), _exceptFds(), _active(true)
{
}

bool UserShell::isShellActive()
{
    return !(std::cin.eof() || !_active);
}

void UserShell::update()
{
    resetCheck();
    setReadFd(STDIN_FILENO);
    setExceptFd(STDIN_FILENO);
    try {
        checkInput();
    } catch (const UserShellError &e) {
        throw e;
    }
    if (checkExceptFd(STDIN_FILENO))
        throw UserShellError("Error with the shell command", "UserShell");
    if (!checkReadFdReady(STDIN_FILENO))
        return;
    getData();
}

std::string UserShell::getUserCommand()
{
    if (_buffer.find('\n') == std::string::npos)
        return (std::string(""));
    std::string line = _buffer.substr(0, _buffer.find('\n') + 1);
    _buffer.erase(0, _buffer.find('\n') + 1);
    return line;
}

void UserShell::resetCheck()
{
    FD_ZERO(&_readFds);
    FD_ZERO(&_exceptFds);
}

void UserShell::setReadFd(int fd)
{
    FD_SET(fd, &_readFds);
}

void UserShell::setExceptFd(int fd)
{
    FD_SET(fd, &_exceptFds);
}


void UserShell::checkInput()
{
    _timeout.tv_usec = 100000;
    if (select(FD_SETSIZE, &_readFds, nullptr, &_exceptFds, &_timeout) == -1)
        throw UserShellError("Error with the shell command", "UserShell");
}

bool UserShell::checkReadFdReady(int fd)
{
    if (FD_ISSET(fd, &_readFds))
        return true;
    return false;
}

bool UserShell::checkExceptFd(int fd)
{
    if (FD_ISSET(fd, &_exceptFds))
        return true;
    return false;
}

void UserShell::getData()
{
    char str[100 + 1];
    bzero(str, 100 + 1);
    if (read(STDIN_FILENO, str, 100) == 0)
        _active = false;
    _buffer.append(str);
}
