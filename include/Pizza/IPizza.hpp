/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_IPIZZA_HPP
#define CPP_PLAZZA_2019_IPIZZA_HPP

#include <map>
#include <iostream>
#include <memory>
#include <thread>

namespace Plazza
{
    class IPizza
    {
        public:
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
        public:
            virtual ~IPizza() = default;

            [[nodiscard]] virtual PizzaType getType() const = 0;
            [[nodiscard]] virtual PizzaSize getSize() const = 0;

            virtual const std::map<size_t, size_t> &getIngredient() = 0;

            [[nodiscard]] virtual bool cook() const = 0;
    };
}

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Plazza::IPizza> &pizza);

#endif //CPP_PLAZZA_2019_IPIZZA_HPP
