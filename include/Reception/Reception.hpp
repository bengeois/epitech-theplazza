/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_RECEPTION_HPP
#define CPP_PLAZZA_2019_RECEPTION_HPP

#include "Error/Error.hpp"
#include <UserShell/UserShell.hpp>
#include <memory>

namespace Plazza
{
    class Reception
    {
        public:
            Reception(float cookingMultiplier, int _cooksPerKitchen, float _stockTime);
            ~Reception() = default;

            void run();

        private:
            float _cookingMultiplier;
            int _cooksPerKitchen;
            float _stockTime;

            std::unique_ptr<UserShell> _shell;

            bool _running;
    };
}

#endif //CPP_PLAZZA_2019_RECEPTION_HPP
