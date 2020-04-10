/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_STOCK_HPP
#define CPP_PLAZZA_2019_STOCK_HPP

#include <map>
#include "Pizza/APizza.hpp"

namespace Plazza
{
    enum Ingredient
    {
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOMS,
        STEAK,
        EGGPLANT,
        GOAT_CHEESE,
        CHIEF_LOVE,
    };

    static const Ingredient availableIngredients[] = {TOMATO, GRUYERE, HAM, MUSHROOMS, STEAK, EGGPLANT, GOAT_CHEESE, CHIEF_LOVE};

    class Stock
    {
        public:
            explicit Stock(size_t stockTime);
            ~Stock() = default;


        private:
            size_t _stockTime;

            std::map<size_t , size_t> _stock;
    };
}

#endif //CPP_PLAZZA_2019_STOCK_HPP
