/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Regina
*/

#ifndef REGINA_HPP_
#define REGINA_HPP_

#include "APizza.hpp"

namespace Plazza
{
    class Regina : public APizza {
        public:
            Regina(PizzaSize size, long cookingMultiplier);
            ~Regina() override = default;

            bool cook() const override;
    };
} // namespace Plazza

#endif /* !REGINA_HPP_ */
