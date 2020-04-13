/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#include "Stock/Stock.hpp"
#include "Pizza/Americana.hpp"

using namespace Plazza;

Americana::Americana(PizzaSize size, long cookingMultiplier) :
    APizza(PizzaType::Americana, size, cookingMultiplier)
{
    _ingredients[Ingredient::DOE] = 1;
    _ingredients[Ingredient::TOMATO] = 1;
    _ingredients[Ingredient::GRUYERE] = 1;
    _ingredients[Ingredient::STEAK] = 1;
}

bool Americana::cook() const
{
    std::this_thread::sleep_for(std::chrono::seconds(2 * _cookingMultiplier));
    return true;
}

