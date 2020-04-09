/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_KITCHEN_HPP
#define CPP_PLAZZA_2019_KITCHEN_HPP

#include "Error/Error.hpp"
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

            template<class F, class ... Args>
            auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

        private:
            // need to keep track of threads so we can join them
            std::vector< std::thread > _cooks;
            // the task queue
            std::queue< std::function<void()> > _tasks;
            // synchronization
            std::mutex _queue_mutex;
            std::condition_variable _condition;
            bool _stop;
            size_t _cookNb;
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

    template<class F, class... Args>
    inline auto Kitchen::enqueue(F&&f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();

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
