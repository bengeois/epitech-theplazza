/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#include "Stock/Stock.hpp"
#include "Pizza/Margarita.hpp"

using namespace Plazza;

Margarita::Margarita(PizzaSize size, long cookingMultiplier) :
APizza(PizzaType::Margarita, size, cookingMultiplier)
{
    _ingredients[Ingredient::DOE] = 1;
    _ingredients[Ingredient::TOMATO] = 1;
    _ingredients[Ingredient::GRUYERE] = 1;
}

bool Margarita::cook() const
{
    std::this_thread::sleep_for(std::chrono::seconds(1 * _cookingMultiplier));
    return true;
}
