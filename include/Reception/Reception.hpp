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
#include "Process/Process.hpp"

namespace Plazza
{
    class Reception
    {
        public:
            Reception(long cookingMultiplier, int _cooksPerKitchen, float
            _stockTime, IIPC::IPCType type = IIPC::SOCKET);
            ~Reception() = default;
            Reception(const Reception &reception);
            Reception &operator=(const Reception &reception);

            void run();

            // Getter and setter
            [[nodiscard]] long getCookingMultiplier() const;
            [[nodiscard]] int getCooksPerKitchen() const;
            [[nodiscard]] float getRegenerateTime() const;
            void setCookingMultiplier(long cookingMultiplier);
            void setCooksPerKitchen(int cooksPerKitchen);
            void setRegenerateTime(float regenerateTime);

        private:
            void createLogDirectory();

            // Processus management
            void translateDataKitchen(const std::string &order);
            const std::string nextStrDataKitchen(const std::string &order, size_t &i) const;
            void readProcess();
            void clearProcess();

            // New order
            void translateCommand(const std::string &command);
            void kitchenProcess();
            void connectKitchen(std::shared_ptr<IIPC> &client);
            void writeOrderToClient(std::shared_ptr<Order> &order, int i, const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza);
            bool clientAcceptOrder(int i);
            void childConnection();
            [[nodiscard]] int getCode(const std::string &res) const;

            // User command status
            [[nodiscard]] bool isStatusCommand(const std::string &command) const;
            void statusCommand();
            void sendStatus(int i);
            void waitResponseStatus(int i);

        private:
            long _cookingMultiplier;
            int _cooksPerKitchen;
            float _regenerateTime;

            std::unique_ptr<Server> _server = nullptr;
            std::vector<std::shared_ptr<Order>> _orders;

            std::string _logDirectory = "";
            std::vector<std::shared_ptr<IProcess>> _process;
            IIPC::IPCType _type = IIPC::SOCKET;
            
    };
}

#endif //CPP_PLAZZA_2019_RECEPTION_HPP
