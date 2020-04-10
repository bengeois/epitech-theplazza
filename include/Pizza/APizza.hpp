/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_APIZZA_HPP
#define CPP_PLAZZA_2019_APIZZA_HPP

#include "IPizza.hpp"

namespace Plazza
{
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8,
    };

    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16,
    };

    class APizza : public IPizza
    {
        public:
            APizza();
            ~APizza() override;

            bool cook() override;
            const std::map<size_t, size_t> &getIngredient() override;

        private:
            std::map<size_t , size_t> _ingredients;

    };
}

#endif //CPP_PLAZZA_2019_APIZZA_HPP
