/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Stock/Stock.hpp"

using namespace Plazza;

Stock::Stock(size_t stockTime) : _stockTime(stockTime)
{
    for ( const auto e : Plazza::availableIngredients)
        _stock[e] = 5;
}
