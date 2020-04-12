/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#ifndef AMERICANA_HPP_
#define AMERICANA_HPP_

#include "APizza.hpp"

namespace Plazza
{
    class Americana : public APizza {
        public:
            Americana(PizzaSize size, long cookingMultiplier);
            ~Americana() override = default;

            bool cook() const override;
    };
} // namespace Plazza

#endif /* !AMERICANA_HPP_ */
