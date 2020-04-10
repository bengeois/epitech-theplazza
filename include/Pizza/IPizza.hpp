/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_IPIZZA_HPP
#define CPP_PLAZZA_2019_IPIZZA_HPP

#include <map>

namespace Plazza
{
    class IPizza
    {
        public:
            virtual ~IPizza() = default;

            virtual bool cook() = 0;
            virtual const std::map<size_t, size_t> &getIngredient() = 0;
    };
}

#endif //CPP_PLAZZA_2019_IPIZZA_HPP
