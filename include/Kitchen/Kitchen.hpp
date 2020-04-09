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
            Kitchen(size_t cooks);
            ~Kitchen();

            auto enqueue(const std::shared_ptr<APizza>& pizza) -> std::future<bool>;
            // ENQUEUE Renvoie un bool true lorsque la fabrication est terminée

        private:
            std::vector< std::thread > _cooks;

            std::queue< std::function<void()> > _tasks;

            std::mutex _queue_mutex;
            std::condition_variable _condition;

            bool _stop;
            size_t _cookNb;

            std::shared_ptr<Stock> _stock;
    };

    inline Kitchen::Kitchen(size_t cooks) : _stop(false), _cookNb(cooks)
    {
        for (size_t i = 0; i < _cookNb; i++) {
            _cooks.emplace_back([this](){
                while (true) {

                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(_queue_mutex);
                        _condition.wait(lock, [this]() {
                            return this->_stop || !this->_tasks.empty();
                        });
                        if (this->_stop && this->_tasks.empty())
                            return;
                        task = std::move(this->_tasks.front());
                        this->_tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    auto Kitchen::enqueue(const std::shared_ptr<APizza> &pizza) -> std::future<bool>
    {

        auto task = std::make_shared<std::packaged_task<bool()>>([pizza, this](){
            pizza->cook();
            return true;
        });

        std::future<bool> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(_queue_mutex);

            if (_stop)
                throw KitchenError("Kitchen Closed", "Kitchen");

            _tasks.emplace([task](){
                (*task)();
            });
        }
        _condition.notify_one();
        return res;
    }

    inline Kitchen::~Kitchen()
    {
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _stop = true;
        }
        _condition.notify_all();
        for (std::thread &cook : _cooks)
            cook.join();
    }
}

#endif //CPP_PLAZZA_2019_KITCHEN_HPP
