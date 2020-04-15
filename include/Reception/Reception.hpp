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
            ~Reception();
            Reception(const Reception &reception);
            Reception &operator=(const Reception &reception);

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

            void writeOrderToClient(std::shared_ptr<Order> &order, int i, const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza);
            bool clientAcceptOrder(int i);
            void childConnection();
            void translateFinishOrder(const std::string &order);
            const std::string nextStrFinishOrder(const std::string &order, size_t &i) const;

            [[nodiscard]] int getCode(const std::string &res) const;

            [[nodiscard]] bool isStatusCommand(const std::string &command) const;
            void statusCommand();

            void sendStatus(int i);
            void waitResponseStatus(int i);

        private:
            long _cookingMultiplier;
            int _cooksPerKitchen;
            float _regenerateTime;

            std::unique_ptr<Server> _server;
            std::vector<std::shared_ptr<Order>> _orders;

            std::string _logDirectory = "";
    };
}

#endif //CPP_PLAZZA_2019_RECEPTION_HPP
