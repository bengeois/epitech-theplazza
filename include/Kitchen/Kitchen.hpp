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
#include <future>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include <algorithm>

namespace Plazza
{
    class Kitchen
    {
        public:
            explicit Kitchen(size_t cooks, float regenerateTime, long cookingMultiplier);
            ~Kitchen();

            // ENQUEUE Renvoie un bool true lorsque la fabrication est terminée
            auto enqueue(const std::shared_ptr<IPizza> &pizza) -> std::future<bool>;

            void run(const std::shared_ptr<Client> &client);

            void checkNewCommand(const std::shared_ptr<Client> &client);
            bool canAcceptPizza(const std::shared_ptr<IPizza> &pizza);

            void checkFinishOrder(const std::shared_ptr<Client> &client);

            void checkActivity();

            std::shared_ptr<IPizza> createPizzaOrder(APizza::PizzaType type, APizza::PizzaSize size, long cookingMultiplier);

            template <class T>
                std::shared_ptr<T> createPizzaOrder(APizza::PizzaSize size, long cookingMultiplier) {
                    std::shared_ptr<T> newPizza = std::make_shared<T>(size, cookingMultiplier);
                    return newPizza;
                }


            private:
                bool _stop;
                bool _noActivity;
                std::chrono::steady_clock::time_point _beginNoActivity;

                long _cookingMultiplier;

                size_t _cookNb;
                std::vector<std::thread> _cooks;

                std::queue<std::function<void()>> _tasks;

                std::mutex _queue_mutex;
                std::condition_variable _condition;

                std::shared_ptr<Stock> _stock;

                std::vector<std::pair<std::pair<size_t, std::shared_ptr<IPizza>>, std::future<bool>>> _orders;
    };
}

#endif //CPP_PLAZZA_2019_KITCHEN_HPP
