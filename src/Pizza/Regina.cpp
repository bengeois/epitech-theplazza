/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Regina
*/

#include "Stock/Stock.hpp"
#include "Pizza/Regina.hpp"

using namespace Plazza;

Regina::Regina(PizzaSize size, long cookingMultiplier) :
    APizza(PizzaType::Regina, size, cookingMultiplier)
{
    _ingredients.at(Ingredient::DOE) = 1;
    _ingredients.at(Ingredient::TOMATO) = 1;
    _ingredients.at(Ingredient::GRUYERE) = 1;
    _ingredients.at(Ingredient::HAM) = 1;
    _ingredients.at(Ingredient::MUSHROOMS) = 1;
}

bool Regina::cook() const
{
    std::this_thread::sleep_for(std::chrono::seconds(2 * _cookingMultiplier));
    return true;
}
