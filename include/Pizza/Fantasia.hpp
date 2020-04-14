/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#ifndef FANTASIA_HPP_
#define FANTASIA_HPP_

#include "APizza.hpp"

namespace Plazza
{
    class Fantasia : public APizza {
        public:
            Fantasia(PizzaSize size, long cookingMultiplier);
            ~Fantasia() override = default;

            [[nodiscard]] bool cook() const override;
    };
} // namespace Plazza

#endif /* !FANTASIA_HPP_ */
