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
            ~APizza();

            bool cook();
            void getIngredient();

        private:
    };
}

#endif //CPP_PLAZZA_2019_APIZZA_HPP
