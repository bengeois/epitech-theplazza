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

using namespace Plazza;

const std::pair<IPizza::PizzaType, const std::string> types[] = {
    {std::make_pair(IPizza::Regina, "regina")},
    {std::make_pair(IPizza::Margarita, "margarita")},
    {std::make_pair(IPizza::Americana, "americana")},
    {std::make_pair(IPizza::Fantasia, "fantasia")},
};

const std::pair<IPizza::PizzaSize, const std::string> sizes[] = {
    {std::make_pair(IPizza::S, "S")},
    {std::make_pair(IPizza::M, "M")},
    {std::make_pair(IPizza::L, "L")},
    {std::make_pair(IPizza::XL, "XL")},
    {std::make_pair(IPizza::XXL, "XXL")},
};

Order::Order(const std::string &order) : _order(order)
{
    static int id = 0;
    std::string tmpOrder = order;

    _id = id++;
    try {
        while (1)
            nextPizza(tmpOrder);
    } catch(const OrderError &e) {
    } catch(const ParserError &e) {
        throw e;
    }
}

Order::~Order()
{
}

const std::string Order::nextWord(std::string &order) const
{
    size_t i = 0;
    std::string word = "";

    for (; order[i] && (order[i] == ';' || order[i] == ' ' || order[i] == '\t'); i++);
    for (; order[i] && order[i] != ' ' && order[i] != ';' && order[i] != '\t'; i++) {
        word += order[i];
    }
    for (; order[i] && (order[i] == ';' || order[i] == ' ' || order[i] == '\t'); i++);
    order.erase(0, i);
    return (word);
}

void Order::nextPizza(std::string &order)
{
    std::string typeWord = nextWord(order);
    std::string sizeWord = nextWord(order);
    std::string numberWord = nextWord(order);
    IPizza::PizzaType type;
    IPizza::PizzaSize size;
    int nb = 0;
    bool error = true;

    for (size_t i = 0; i < 4; i++) {
        if (types[i].second != typeWord)
            continue;
        type = types[i].first;
        error = false;
        break;
    }
    if (error)
        throw ParserError("Wrong parsing, cannot find the type", "nextPizza");
    error = true;
    for (size_t i = 0; i < 5; i++) {
        if (sizes[i].second != sizeWord)
            continue;
        size = sizes[i].first;
        error = false;
        break;
    }
    if (error)
        throw ParserError("Wrong argument, cannot find the size", "nextPizza");
    if (numberWord[0] != 'x')
        throw ParserError("Wrong argument, cannot find the number", "nextPizza");
    std::string tmpNumber = "";
    for (size_t i = 1; numberWord[i]; i++) {
        tmpNumber += numberWord[i];
    }
    try {
        nb = std::stoi(tmpNumber);
    } catch(const std::exception& e) {
        throw ParserError("Wrong argument, wrong number", "nextPizza");
    }
    for (int i = 0; i < nb; i++) {
        _pizzas.push_back(std::make_tuple(type, size, false, false));
    }
    if (order.size() == 0)
        throw OrderError("No more pizza");
}

std::unique_ptr<IPizza> Order::getNextPizza() const
{
    return (std::make_unique<Margarita>());
}

void Order::addPizzaFinish(IPizza::PizzaType type, IPizza::PizzaSize size)
{
    (void)type;
    (void)size;
}

void Order::pack()
{
}

bool Order::isFinish() const
{
    auto pizza = std::find_if_not(_pizzas.begin(), _pizzas.end(), [](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        return (std::get<2>(pizza));
    });

    return (pizza == _pizzas.end());
}