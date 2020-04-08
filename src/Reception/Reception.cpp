/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"

using namespace Plazza;

Reception::Reception(float cookingMultiplier, int cooksPerKitchen, float stockTime) :
_cookingMultiplier(cookingMultiplier),
_cooksPerKitchen(cooksPerKitchen),
_stockTime(stockTime),
_shell(std::make_unique<UserShell>())
{

}

void Reception::run()
{
    while (1) {
        _shell->getUserCommand();
    }
}