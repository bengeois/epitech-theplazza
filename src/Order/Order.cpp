/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#include "Order/Order.hpp"
#include "Error/Error.hpp"
#include <algorithm>
#include <iostream>
#include "File.hpp"
#include "Utils.hpp"
#include <filesystem>

using namespace Plazza;

Order::Order(const std::string &order, int cookingMultiplier) : _order(order), _cookingMultiplier(cookingMultiplier)
{
    static int id = 0;
    std::string tmpOrder = order;

    tmpOrder.erase(0, tmpOrder.find_first_not_of("; \t"));
    try {
        while (nextPizza(tmpOrder));
    } catch(const ParserError &e) {
        throw e;
    }
    _id = id++;
}

const std::string Order::nextWord(std::string &order, bool extremity) const
{
    int begin = 0;
    std::string word = "";
    int end = 0;

    begin = order.find_first_not_of(" \t");
    end = order.find_first_of((extremity ? " \t;\n" : " \t\n"), begin);
    if (end == -1) {
        order = "";
        return (word);
    }
    word = order.substr(begin, end);
    end = order.find_first_not_of((extremity ? " \t;\n" : " \t\n"), end);
    order.erase(0, end);
    return (word);
}

bool Order::nextPizza(std::string &order)
{
    std::string typeWord = nextWord(order, false);
    std::string sizeWord = nextWord(order, false);
    std::string numberWord = nextWord(order, true);
    IPizza::PizzaType type;
    IPizza::PizzaSize size;
    int nb = 0;

    try {
        type = Utils::getPizzaType(Utils::toLower(typeWord));
        size = Utils::getPizzaSize(sizeWord);
    } catch(const UtilsError& e) {
        throw ParserError("Wrong command", "nextPizza");
    }

    if (numberWord.size() <= 1 || numberWord[0] != 'x' || numberWord[1] <= '0' || numberWord[1] > '9')
        throw ParserError("Wrong argument, cannot find the number", "nextPizza");
    try {
        nb = std::stoi(numberWord.substr(1, numberWord.size()));
    } catch(const std::exception& e) {
        throw ParserError("Wrong argument, wrong number", "nextPizza");
    }
    for (int i = 0; i < nb; i++) {
        _pizzas.emplace_back(type, size, false, false);
    }
    if (order.empty())
        return (false);
    return (true);
}

std::shared_ptr<IPizza> Order::getNextPizza() const
{
    auto pizza = std::find_if_not(_pizzas.begin(), _pizzas.end(), [](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        return (std::get<3>(pizza));
    });

    if (pizza == _pizzas.end())
        throw OrderError("No more pizza");
    std::map<IPizza::PizzaType, std::shared_ptr<IPizza> (Order::*)(IPizza::PizzaSize) const> pizzas;

    pizzas[IPizza::Americana] = &Order::createAmericana;
    pizzas[IPizza::Fantasia] = &Order::createFantasia;
    pizzas[IPizza::Margarita] = &Order::createMargarita;
    pizzas[IPizza::Regina] = &Order::createRegina;
    return ((this->*pizzas[std::get<0>(*pizza)])(std::get<1>(*pizza)));
}

void Order::addPizzaFinish(IPizza::PizzaType type, IPizza::PizzaSize size)
{
    if (isFinish())
        throw OrderError("Unable to add pizza", "addPizzaFinish");
    auto pizza = std::find_if(_pizzas.begin(), _pizzas.end(), [&type, &size](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        if (std::get<2>(pizza))
            return (false);
        return std::get<0>(pizza) == type && std::get<1>(pizza) == size;
    });

    std::get<2>(*pizza) = true;
}

void Order::pack(const std::string &folderPath)
{
    std::filesystem::create_directory("logs");
    std::filesystem::create_directory("logs/" + folderPath);

    std::cout << "[RECEPTION] Order n°" << std::to_string(_id) << " completed" << std::endl;
    File file("logs/" + folderPath + "/order-" + std::to_string(_id) + ".plazza", std::ios::out);

    file << "----------------Order " << std::to_string(_id) << "----------------" << std::endl;
    std::for_each(_pizzas.begin(), _pizzas.end(), [&file](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        file << "1 " << Utils::getStringPizzaType(std::get<0>(pizza)) << " of size " << Utils::getStringPizzaSize(std::get<1>(pizza)) << (std::get<3>(pizza) ? "" : " not send to a kitchen yet") << (std::get<2>(pizza) ? " cooked" : "") << std::endl;
    });
}

bool Order::isFinish() const
{
    auto pizza = std::find_if_not(_pizzas.begin(), _pizzas.end(), [](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        return (std::get<2>(pizza));
    });

    return (pizza == _pizzas.end());
}

std::shared_ptr<IPizza> Order::createMargarita(IPizza::PizzaSize size) const
{
    return (std::make_shared<Margarita>(size, _cookingMultiplier));
}

std::shared_ptr<IPizza> Order::createAmericana(IPizza::PizzaSize size) const
{
    return (std::make_shared<Americana>(size, _cookingMultiplier));
}

std::shared_ptr<IPizza> Order::createRegina(IPizza::PizzaSize size) const
{
    return (std::make_shared<Regina>(size, _cookingMultiplier));
}

std::shared_ptr<IPizza> Order::createFantasia(IPizza::PizzaSize size) const
{
    return (std::make_shared<Fantasia>(size, _cookingMultiplier));
}

int Order::getId() const
{
    return (_id);
}

const std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> &Order::getPizzas() const
{
    return (_pizzas);
}

void Order::setSend(int i, send_t send)
{
    std::get<3>(_pizzas[i]) = send;
}

std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Plazza::Order> &order)
{
    const std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> pizzas = order->getPizzas();

    os << "----------------Order " << order->getId() << "----------------";
    std::for_each(pizzas.begin(), pizzas.end(), [&os](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        os << std::endl;
        os << "1 " << Utils::getStringPizzaType(std::get<0>(pizza)) << " of size " << Utils::getStringPizzaSize(std::get<1>(pizza)) << (std::get<3>(pizza) ? "" : " not send to a kitchen yet") << (std::get<2>(pizza) ? " ready" : "");
    });
    return (os);
}