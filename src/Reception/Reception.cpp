/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"

#include <iostream>

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
{
    std::string command;
    while (_running) {
        try {
            command = _shell->getUserCommand();
        } catch (const UserShellError &e) {
            throw e;
        }
        if (!command.empty())
            std::cout << command << std::endl;
        if (!_shell->isShellActive())
            _running = false;
    }
}