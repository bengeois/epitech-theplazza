/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <sstream>
#include <zconf.h>
#include <csignal>
#include <LockGuard/LockGuard.hpp>
#include "Pizza/APizza.hpp"
#include "Pizza/Americana.hpp"
#include "Pizza/Margarita.hpp"
#include "Pizza/Regina.hpp"
#include "Pizza/Fantasia.hpp"
#include "Kitchen/Kitchen.hpp"

using namespace Plazza;

static bool kill_kitchen = false;

void signal_handler(int signal_num)
{
    if (signal_num == SIGINT)
        kill_kitchen = true;
}

Kitchen::Kitchen(size_t cooks, float regenerateTime, long cookingMultiplier) :
_stop(false),
_noActivity(false),
_cookingMultiplier(cookingMultiplier),
_cookNb(cooks),
_queue_mutex(std::make_shared<Mutex>()),
_stock(std::make_shared<Stock>(Stock(regenerateTime)))
{
    _id = getpid();
    _cooks.reserve(_cookNb);

    std::function<void()> ft = [this]()
        {
            while (true) {

                std::function<void()> task;

                {
                    LockGuard lock(_queue_mutex);
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
        };

    for (size_t i = 0; i < _cookNb; i++)
        _cooks.emplace_back(std::make_shared<Thread>(ft));
}

Kitchen::~Kitchen()
{
    {
        LockGuard lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::shared_ptr<Thread> &cook : _cooks)
        cook->join();
}


auto Kitchen::enqueue(const std::shared_ptr<IPizza> &pizza) -> std::future<bool>
{

    auto task = std::make_shared<std::packaged_task<bool()>>([pizza, this](){
        return pizza->cook();
    });

    std::future<bool> res = task->get_future();

    {
        LockGuard lock(_queue_mutex);

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

void Kitchen::run(const std::shared_ptr<IIPC> &client)
{
    std::signal(SIGINT, signal_handler);
    try {
        while (!_stop && !kill_kitchen) {
            this->checkActivity();
            _stock->regenerateIngredient();
            this->checkFinishOrder(client);
            this->receiveFromReception(client);
            client->send();
        }
    } catch (const PlazzaError &e) {
        throw e;
    }
    std::cout << "[KITCHEN " << _id << "] No more pizza to cook, kitchen close its doors" << std::endl;
}

bool Kitchen::canAcceptPizza(const std::shared_ptr<IPizza> &pizza)
{
    if (_orders.size() + 1 > (2 * _cookNb))
        return false;
    return (_stock->canCookPizza(pizza));
}

void Kitchen::checkFinishOrder(const std::shared_ptr<IIPC> &client)
{
    _orders.erase(std::remove_if(_orders.begin(), _orders.end(), [this, client](const auto &order){
        if (future_ready(order.second)) {
            client->send(std::string(
                "300 "
                + std::to_string(order.first.first)
                + " "
                + Utils::getStringPizzaType(order.first.second->getType())
                + " "
                + Utils::getStringPizzaSize(order.first.second->getSize())
                + "\n"));
            std::cout << "[KITCHEN " << _id << "] Order n°" << order.first.first << " "
            << Utils::getStringPizzaType(order.first.second->getType()) << " "
            << Utils::getStringPizzaSize(order.first.second->getSize()) << " is ready." << std::endl;
            return true;
        }
        return false;
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


void Kitchen::receiveFromReception(const std::shared_ptr<IIPC> &client)
{
    try {
        client->read();
    } catch (const ClientError &e) {
    }

    std::string pingReception = client->getData();
    if (pingReception.empty())
        return;
    if (pingReception.substr(0, 3) == "500")
        return sendKitchenStatus(client);
    return checkNewCommand(client, pingReception);
}


void Kitchen::sendKitchenStatus(const std::shared_ptr<IIPC> &client) const
{
    std::cout << std::endl << "[KITCHEN " << _id << "]" << std::endl;
    std::cout << "\t[Number ok cook] " << _cookNb << std::endl;
    std::cout << "\t[Cooking Time] " << _cookingMultiplier << std::endl;
    std::cout << "\t[Stock] Regeneration time : " << _stock->getRegenerateTime() << " milliseconds." << std::endl;
    for (const auto &ingredient : _stock->getStock())
        std::cout << "\t\t" << Utils::getStringIngredient(static_cast<Ingredient>(ingredient.first)) << " -> " << ingredient.second << std::endl;
    std::cout << "\t[Order in progress] " << _orders.size() << std::endl;
    for (const auto &order : _orders)
        std::cout << "\t\tOrder n°" << order.first.first << " " << Utils::getStringPizzaType(order.first.second->getType()) << " " << Utils::getStringPizzaSize(order.first.second->getSize()) << std::endl;
    std::cout << std::endl;
    client->send(std::string("400\n"));
}

void Kitchen::checkNewCommand(const std::shared_ptr<IIPC> &client, const std::string &pingReception)
{
    size_t orderID;
    std::string pizzaType;
    std::string pizzaSize;

    std::istringstream ss(pingReception);
    ss >> orderID;
    ss >> pizzaType;
    ss >> pizzaSize;

    std::shared_ptr<IPizza> preparationPizza = createPizza(
        Utils::getPizzaType(pizzaType),
        Utils::getPizzaSize(pizzaSize),
        _cookingMultiplier
        );
    if (!canAcceptPizza(preparationPizza)) {
        client->send(std::string("100 0\n"));
        return;
    }
    std::pair<size_t, std::shared_ptr<IPizza>> orderInfos(orderID, preparationPizza);
    _orders.emplace_back(
        std::pair<std::pair<size_t, std::shared_ptr<IPizza>>, std::future<bool>>(
            orderInfos,
            enqueue(preparationPizza)
            )
        );
    client->send(std::string("100 1\n"));
}

std::shared_ptr<IPizza> Kitchen::createPizza(APizza::PizzaType type, APizza::PizzaSize size, long cookingMultiplier)
{
    if (type == IPizza::Americana)
        return createPizza<Americana>(size, cookingMultiplier);
    if (type == IPizza::Fantasia)
        return createPizza<Fantasia>(size, cookingMultiplier);
    if (type == IPizza::Margarita)
        return createPizza<Margarita>(size, cookingMultiplier);
    return createPizza<Regina>(size, cookingMultiplier);
}

int Kitchen::getID() const
{
    return _id;
}