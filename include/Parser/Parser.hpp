/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_PARSER_HPP
#define CPP_PLAZZA_2019_PARSER_HPP

#include <string>
#include <vector>
#include "Error/Error.hpp"

namespace Plazza
{
    class Parser
    {
        public:
            Parser(int argc, char **argv);
            ~Parser() = default;

            void build();

            float getCookingMultiplier() const;
            int getCooksPerKitchen() const;
            float getStockTime() const;

        private:
            const std::vector<std::string> _argv;
            float _cookingMultiplier;
            int _cooksPerKitchen;
            float _stockTime;
    };
}

#endif //CPP_PLAZZA_2019_PARSER_HPP
