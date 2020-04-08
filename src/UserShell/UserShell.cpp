/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <iostream>
#include "UserShell/UserShell.hpp"

using namespace Plazza;

UserShell::UserShell() : _readFds(), _writeFds(), _exceptFds()
{
}

const std::string &UserShell::getUserCommand()
{
    resetCheck();
    _command.clear();
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
        return _command;
    getline(std::cin, _command);
    return _command;
}

bool UserShell::isShellActive()
{
    return !std::cin.eof();
}

void UserShell::checkInput()
{
    _timeout.tv_usec = 100000;
    if (select(FD_SETSIZE, &_readFds, &_writeFds, &_exceptFds, &_timeout) == -1)
        throw UserShellError("Error with the shell command", "UserShell");
}

void UserShell::resetCheck()
{
    FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
    FD_ZERO(&_exceptFds);
}

void UserShell::setReadFd(int fd)
{
    FD_SET(fd, &_readFds);
}

void UserShell::setWriteFd(int fd)
{
    FD_SET(fd, &_writeFds);
}

void UserShell::setExceptFd(int fd)
{
    FD_SET(fd, &_exceptFds);
}

bool UserShell::checkReadFdReady(int fd)
{
    if (FD_ISSET(fd, &_readFds))
        return true;
    return false;
}

bool UserShell::checkWriteFdReady(int fd)
{
    if (FD_ISSET(fd, &_writeFds))
        return true;
    return false;
}

bool UserShell::checkExceptFd(int fd)
{
    if (FD_ISSET(fd, &_exceptFds))
        return true;
    return false;
}