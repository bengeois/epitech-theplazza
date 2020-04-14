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
    class APizza : public IPizza
    {
        public:
            APizza(PizzaType type, PizzaSize size, long cookingMultiplier);
            ~APizza() override = default;


            [[nodiscard]] PizzaType getType() const override;
            [[nodiscard]] PizzaSize getSize() const override;

            const std::map<size_t, size_t> &getIngredient() override;

            [[nodiscard]] bool cook() const override = 0;

        protected:
            const PizzaType _type;
            const PizzaSize _size;
            const long _cookingMultiplier;
            std::map<size_t, size_t> _ingredients;

    };
}

#endif //CPP_PLAZZA_2019_APIZZA_HPP
