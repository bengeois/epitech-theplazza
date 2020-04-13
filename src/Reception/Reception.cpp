/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"
#include "Socket/Client.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Utils.hpp"

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace Plazza;

Reception::Reception(long cookingMultiplier, int cooksPerKitchen, float
regenerateTime) :
    _cookingMultiplier(cookingMultiplier),
    _cooksPerKitchen(cooksPerKitchen),
    _regenerateTime(regenerateTime),
    _shell(std::make_unique<UserShell>()),
    _server(std::make_unique<Server>()),
    _running(true)
{

}

void Reception::run()
{
    std::string command;
    fd_set writefs;
    fd_set readfs;

    while (!std::cin.eof()) {
        resetFdSet(&readfs, &writefs);
        FD_SET(1, &readfs);
        _server->setFdSet(&readfs, &writefs);
        if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
            throw ReceptionError("Select fail", "Select");
        translateSelect(readfs, writefs);
    }
}

const std::string Reception::nextStrFinishOrder(const std::string &order, size_t &i) const
{
    if (order[i] == ' ')
        i++;
    std::string data = "";
    for (; order[i] != '\n' && order[i] != ' '; i++) {
        data += order[i];
    }
    return (data);
}

void Reception::translateFinishOrder(const std::string &order)
try {
    std::string nOrderStr = "";
    std::string typeStr = "";
    std::string sizeStr = "";
    size_t i = 4;

    if (order.size() <= 4)
        throw ReceptionError("Invalide response from the client", "tranlateFinishOrder");
    nOrderStr = nextStrFinishOrder(order, i);
    typeStr = nextStrFinishOrder(order, i);
    sizeStr = nextStrFinishOrder(order, i);

    int nOrder = std::stoi(nOrderStr);
    IPizza::PizzaType type = Utils::getPizzaType(typeStr);
    IPizza::PizzaSize size = Utils::getPizzaSize(sizeStr);
    auto orderIt = std::find_if(_orders.begin(), _orders.end(), [&nOrder](std::shared_ptr<Order> &order) -> bool {
        return (nOrder == order->getId());
    });

    (*orderIt)->addPizzaFinish(type, size);
    if ((*orderIt)->isFinish()) {
        (*orderIt)->pack();
        _orders.erase(orderIt);
    }
} catch (const std::exception &e) {
    throw ReceptionError("Invalid response for the client", "translateFinishOrder");
}

void Reception::translateSelect(const fd_set &readfs, const fd_set &writefs)
{
    if (FD_ISSET(1, &readfs)) {
        std::string command;

        std::getline(std::cin, command);
        if (!command.empty())
            translateCommand(command);
    }
    _server->translateSelect(readfs, writefs);
    for (int i = 0; i < _server->getNbClient(); i++) {
        std::string data;
        if ((data = _server->getClientAt(i)->getData()).size() == 0)
            continue;
        translateFinishOrder(data);
    }
}

void Reception::resetFdSet(fd_set *readfs, fd_set *writefs)
{
    FD_ZERO(readfs);
    FD_ZERO(writefs);
}

void Reception::writeOrderToClient(std::shared_ptr<Order> &order, int i, const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza)
{
    _server->getClientAt(i)->write(std::string(std::to_string(order->getId()) + " " + Utils::getStringPizzaType(std::get<0>(pizza)) + " " + Utils::getStringPizzaSize(std::get<1>(pizza)) + "\n"));
    fd_set writefs;
    fd_set readfs;

    while (_server->getClientAt(i)->isWriting()) {
        resetFdSet(&readfs, &writefs);
        _server->getClientAt(i)->setFdSet(&readfs, &writefs);
        if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
            throw ReceptionError("Select fail", "Select");
        _server->getClientAt(i)->translateSelect(readfs, writefs);
    }
}

int Reception::getCode(const std::string &res) const
{
    std::string codeStr = "";

    for (int i = 0; res[i] != '\n' && res[i] != ' '; i++) {
        if (!(res[i] >= '0' && res[i] <= '9'))
            throw ReceptionError("Invalid code response", "getCode");
        codeStr += res[i];
    }
    return (std::stoi(codeStr));
}

bool Reception::clientAcceptOrder(int i)
{
    std::string data = "";
    fd_set writefs;
    fd_set readfs;

    while (data.size() == 0 || getCode(data) != 100) {
        resetFdSet(&readfs, &writefs);
        _server->getClientAt(i)->setFdSet(&readfs, &writefs);
        if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
            throw ReceptionError("Select fail", "Select");
        _server->getClientAt(i)->translateSelect(readfs, writefs);
        data = _server->getClientAt(i)->getData();
        if (data.size() != 0 && getCode(data) == 300)
            translateFinishOrder(data);
    }
    if (data == "100 1\n")
        return (true);
    return (false);
}

void Reception::childConnection()
{
    int fd = _server->getFd();
    fd_set writefs;
    fd_set readfs;

    resetFdSet(&readfs, &writefs);
    FD_SET(fd, &readfs);
    if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
        throw ReceptionError("Select fail", "childConnection");
    _server->newConnection();
}

void Reception::translateCommand(const std::string &command)
try {
    std::shared_ptr<Order> order = std::make_shared<Order>(command, _cookingMultiplier);

    std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> pizzas = order->getPizzas();
    std::cout << order << std::endl;

    std::for_each(pizzas.begin(), pizzas.end(), [this, &order](std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        // Find a kitchen which can accept the pizza
        for (int i = 0; i < _server->getNbClient(); i++) {
            writeOrderToClient(order, i, pizza);
            if (clientAcceptOrder(i)) {
                std::get<3>(pizza) = true;
                return;
            }
        }
        // Fork if no kitchen can take the pizza
        pid_t child = fork();

        if (child == -1)
            throw ReceptionError("Fork failed");
        if (child == 0)
            kitchenProcess();
        childConnection();
        writeOrderToClient(order, _server->getNbClient() - 1, pizza);
        if (!clientAcceptOrder(_server->getNbClient() - 1))
            throw ReceptionError("Fatal error : Unable to send the pizza");
    });
    _orders.push_back(order);

} catch (const ParserError &e) {
    std::cout << "Invalid command" << std::endl;
}

long Reception::getCookingMultiplier() const
{
    return _cookingMultiplier;
}

int Reception::getCooksPerKitchen() const
{
    return _cooksPerKitchen;
}

float Reception::getRegenerateTime() const
{
    return _regenerateTime;
}

void Reception::setCookingMultiplier(long cookingMultiplier)
{
    _cookingMultiplier = cookingMultiplier;
}

void Reception::setCooksPerKitchen(int cooksPerKitchen)
{
    _cooksPerKitchen = cooksPerKitchen;
}

void Reception::setRegenerateTime(float regenerateTime)
{
    _regenerateTime = regenerateTime;
}