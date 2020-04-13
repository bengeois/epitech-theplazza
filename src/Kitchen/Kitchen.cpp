/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <sstream>
#include "Pizza/APizza.hpp"
#include "Pizza/Americana.hpp"
#include "Pizza/Margarita.hpp"
#include "Pizza/Regina.hpp"
#include "Pizza/Fantasia.hpp"
#include "Kitchen/Kitchen.hpp"

using namespace Plazza;

Kitchen::Kitchen(size_t cooks, float regenerateTime, long cookingMultiplier) :
_stop(false),
_noActivity(false),
_cookingMultiplier(cookingMultiplier),
_cookNb(cooks),
_stock(std::make_shared<Stock>(Stock(regenerateTime)))
{
    _cooks.reserve(_cookNb);
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

        _stock->reserveIngredient(pizza);
        _tasks.emplace([task](){
            (*task)();
        });
    }
    _condition.notify_one();
    return res;
}

void Kitchen::run(const std::shared_ptr<Client> &client)
{
    try {
        while (!_stop) {
            this->checkActivity();
            _stock->regenerateIngredient();
            this->checkFinishOrder(client);
            this->checkNewCommand(client);
        }
    } catch (const PlazzaError &e) {
        throw e;
    }
}

bool Kitchen::canAcceptPizza(const std::shared_ptr<IPizza> &pizza)
{
    if (_orders.size() + 1 > (2 * _cookNb))
        return false;
    return (_stock->canCookPizza(pizza));
}

void Kitchen::checkFinishOrder(const std::shared_ptr<Client> &client)
{
    for (const auto &order : _orders) {
        if (future_ready(order.second)) {
            client->write(std::string(
                "300 "
                + std::to_string(order.first.first)
                + " "
                + Utils::getStringPizzaType(order.first.second->getType())
                + " "
                + Utils::getStringPizzaSize(order.first.second->getSize())
                + "\n"));
        }
    }
    _orders.erase(std::remove_if(_orders.begin(), _orders.end(), [](const auto &order){
        return future_ready(order.second);
    }), _orders.end());
}

void Kitchen::checkActivity()
{
    if (!_orders.empty()) {
        _noActivity = false;
        return;
    }
    if (!_noActivity) {
        _noActivity = !_noActivity;
        _beginNoActivity = std::chrono::steady_clock::now();
        return;
    }
    std::chrono::steady_clock::time_point endNoActivity = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(endNoActivity - _beginNoActivity).count() < 5)
        return;
    _stop = true;
}

void Kitchen::checkNewCommand(const std::shared_ptr<Client> &client)
{
    size_t orderID;
    std::string pizzaType;
    std::string pizzaSize;
    try {
        client->read();
    } catch (const ClientError &e) {
        throw e;
    }

    std::string pingReception = client->getData();
    if (pingReception.empty())
        return;

    std::istringstream ss(pingReception);
    ss >> orderID;
    ss >> pizzaType;
    ss >> pizzaSize;

    std::shared_ptr<IPizza> preparationPizza = createPizzaOrder(Utils::getPizzaType(pizzaType), Utils::getPizzaSize(pizzaSize), _cookingMultiplier);
    if (!canAcceptPizza(preparationPizza)) {
        client->write(std::string("100 " + std::to_string(orderID) + " 0\n"));
        return;
    }
    std::pair<std::pair<size_t, std::shared_ptr<IPizza>>, std::future<bool>> orderAll(std::pair<size_t, std::shared_ptr<IPizza>>(orderID, preparationPizza), enqueue(preparationPizza));
    client->write(std::string("100 " + std::to_string(orderID) + " 1\n"));
}

std::shared_ptr<IPizza> Kitchen::createPizzaOrder(APizza::PizzaType type, APizza::PizzaSize size, long cookingMultiplier)
{
    if (type == IPizza::Americana)
        return createPizzaOrder<Americana>(size, cookingMultiplier);
    if (type == IPizza::Fantasia)
        return createPizzaOrder<Fantasia>(size, cookingMultiplier);
    if (type == IPizza::Margarita)
        return createPizzaOrder<Margarita>(size, cookingMultiplier);
    return createPizzaOrder<Regina>(size, cookingMultiplier);
}
