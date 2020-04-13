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
            Reception(long cookingMultiplier, int _cooksPerKitchen, float
            _stockTime);
            ~Reception() = default;

            void run();

            long getCookingMultiplier() const;
            int getCooksPerKitchen() const;
            float getRegenerateTime() const;

            void setCookingMultiplier(long cookingMultiplier);
            void setCooksPerKitchen(int cooksPerKitchen);
            void setRegenerateTime(float regenerateTime);

        private:
            void translateCommand(const std::string &command);
            void resetFdSet(fd_set *readfs, fd_set *writefs);
            void translateSelect(const fd_set &read, const fd_set &writefs);

            void kitchenProcess();
            void connectKitchen(std::shared_ptr<Client> &client);

        private:
            long _cookingMultiplier;
            int _cooksPerKitchen;
            float _regenerateTime;

            std::unique_ptr<UserShell> _shell;
            std::unique_ptr<Server> _server;
            std::vector<std::shared_ptr<Order>> _orders;

            bool _running;
    };
}

#endif //CPP_PLAZZA_2019_RECEPTION_HPP
