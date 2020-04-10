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
            APizza();
            ~APizza() override;

            bool cook() override;
            const std::map<size_t, size_t> &getIngredient() override;

        private:
            std::map<size_t , size_t> _ingredients;

    };
}

#endif //CPP_PLAZZA_2019_APIZZA_HPP
