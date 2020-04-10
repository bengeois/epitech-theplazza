/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Kitchen/Kitchen.hpp"

using namespace Plazza;

Kitchen::Kitchen(size_t cooks, float stockTime) :
_stop(false),
_cookNb(cooks),
_stock(std::make_shared<Stock>(Stock(stockTime)))
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

Kitchen::~Kitchen()
{
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::thread &cook : _cooks)
        cook.join();
}


auto Kitchen::enqueue(const std::shared_ptr<IPizza> &pizza) -> std::future<bool>
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

void Kitchen::run()
{

}

void Kitchen::canAcceptPizza(const std::shared_ptr<IPizza> &pizza)
{

}