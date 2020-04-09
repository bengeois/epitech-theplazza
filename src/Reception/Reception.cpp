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
    _running(true)
{

}

void Reception::run()
try {
    std::string command;
    while (_running) {
        command = _shell->getUserCommand();
        if (!command.empty())
            translateCommand(command);
        if (!_shell->isShellActive())
            _running = false;
    }
} catch (const UserShellError &e) {
    throw e;
}

void Reception::translateCommand(const std::string &command) const
{
    (void)command;
}