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
#include "Socket/Client.hpp"
#include "Socket/Server.hpp"
#include "Order/Order.hpp"

namespace Plazza
{
    class Reception
    {
        public:
            Reception(float cookingMultiplier, int _cooksPerKitchen, float _stockTime);
            ~Reception() = default;

            void run();

        private:
            void translateCommand(const std::string &command);
            void resetFdSet(fd_set *readfs, fd_set *writefs);
            void translateSelect(const fd_set &read, const fd_set &writefs);

        private:
            float _cookingMultiplier;
            int _cooksPerKitchen;
            float _stockTime;

            std::unique_ptr<UserShell> _shell;
            std::unique_ptr<Server> _server;
            std::vector<std::unique_ptr<Order>> _orders;

            bool _running;
    };
}

#endif //CPP_PLAZZA_2019_RECEPTION_HPP
