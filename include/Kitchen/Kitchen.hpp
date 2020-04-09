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
#include <future>
#include <vector>
#include <queue>
#include <memory>
#include <functional>

namespace Plazza
{
    class Kitchen
    {
        public:
            explicit Kitchen(size_t cooks);
            ~Kitchen();

            // ENQUEUE Renvoie un bool true lorsque la fabrication est terminée
            auto enqueue(const std::shared_ptr<APizza> &pizza) -> std::future<bool>;

        private:
            std::vector<std::thread> _cooks;

            std::queue<std::function<void()>> _tasks;

            std::mutex _queue_mutex;
            std::condition_variable _condition;

            bool _stop;
            size_t _cookNb;

            std::shared_ptr<Stock> _stock;
    };
}

#endif //CPP_PLAZZA_2019_KITCHEN_HPP
