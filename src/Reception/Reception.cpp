/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"
#include "Socket/Client.hpp"

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace Plazza;

Reception::Reception(float cookingMultiplier, int cooksPerKitchen, float stockTime) :
    _cookingMultiplier(cookingMultiplier),
    _cooksPerKitchen(cooksPerKitchen),
    _stockTime(stockTime),
    _shell(std::make_unique<UserShell>()),
    _server(std::make_unique<Server>()),
    _running(true)
{

}

void Reception::run()
try {
    std::string command;
    fd_set writefs;
    fd_set readfs;

    while (!std::cin.eof()) {
        resetFdSet(&readfs, &writefs);
        FD_SET(1, &readfs);
        _server->setFdSet(&readfs, &writefs);
        if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
            throw ReceptionError("Select fail", "Select");
        translateSelect(readfs, writefs);
    }
} catch (const UserShellError &e) {
    throw e;
}

void Reception::translateSelect(const fd_set &readfs, const fd_set &writefs)
{
    (void)writefs;
    if (FD_ISSET(1, &readfs)) {
        std::string command;

        std::getline(std::cin, command);
        if (!command.empty())
            std::cout << command << std::endl;
    }
}

void Reception::resetFdSet(fd_set *readfs, fd_set *writefs)
{
    FD_ZERO(readfs);
    FD_ZERO(writefs);
}

void Reception::translateCommand(const std::string &command) const
{
    (void)command;
}