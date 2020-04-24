/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_KITCHEN_HPP
#define CPP_PLAZZA_2019_KITCHEN_HPP

#include "Error/Error.hpp"
#include "Pizza/APizza.hpp"
#include "Stock/Stock.hpp"
#include "Socket/Client.hpp"
#include "Utils.hpp"
#include "Thread/Thread.hpp"
#include "Mutex/Mutex.hpp"
#include "IPC/Socket.hpp"
#include <future>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include <algorithm>
#include <ConditionVariable/ConditionVariable.hpp>

namespace Plazza
{
    class Kitchen
    {
        public:
            explicit Kitchen(size_t cooks, float regenerateTime, long cookingMultiplier);
            ~Kitchen();

            void run(const std::shared_ptr<IIPC> &client);

            auto enqueue(const std::shared_ptr<IPizza> &pizza) -> std::future<bool>;

            [[nodiscard]] int getID() const;

        private:
            void checkActivity();
            void receiveFromReception(const std::shared_ptr<IIPC> &client);
            void sendKitchenStatus(const std::shared_ptr<IIPC> &client) const;
            void checkNewCommand(const std::shared_ptr<IIPC> &client, const std::string &pingReception);
            bool canAcceptPizza(const std::shared_ptr<IPizza> &pizza);
            void checkFinishOrder(const std::shared_ptr<IIPC> &client);

            template <class T>
            std::shared_ptr<T> createPizza(APizza::PizzaSize size, long cookingMultiplier) {
                std::shared_ptr<T> newPizza = std::make_shared<T>(size, cookingMultiplier);
                return newPizza;
            }

            std::shared_ptr<IPizza> createPizza(APizza::PizzaType type, APizza::PizzaSize size, long cookingMultiplier);

        private:
                int _id;
                bool _stop;
                bool _noActivity;
                std::chrono::steady_clock::time_point _beginNoActivity;

                long _cookingMultiplier;

                size_t _cookNb;
                std::vector<std::shared_ptr<Thread>> _cooks;

                std::queue<std::function<void()>> _tasks;

                std::shared_ptr<Mutex> _queue_mutex;
                ConditionVariable _condition;
                //std::condition_variable _condition;

                std::shared_ptr<Stock> _stock;

                std::vector<std::pair<std::pair<size_t, std::shared_ptr<IPizza>>, std::future<bool>>> _orders;
    };
}

#endif //CPP_PLAZZA_2019_KITCHEN_HPP
