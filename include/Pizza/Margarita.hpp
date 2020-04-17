/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#ifndef MARGARITA_HPP_
#define MARGARITA_HPP_

#include "APizza.hpp"

namespace Plazza
{
    class Margarita : public APizza {
        public:
            Margarita(PizzaSize size, long cookingMultiplier);
            ~Margarita() override = default;
            Margarita(const Margarita &margarita) = default;
            Margarita &operator=(const Margarita &margarita) = default;

            [[nodiscard]] bool cook() const override;
    };
} // namespace Plazza

#endif /* !MARGARITA_HPP_ */
