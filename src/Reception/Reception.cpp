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
#include <ctime>

using namespace Plazza;

Reception::Reception(long cookingMultiplier, int cooksPerKitchen, float
regenerateTime) :
    _cookingMultiplier(cookingMultiplier),
    _cooksPerKitchen(cooksPerKitchen),
    _regenerateTime(regenerateTime),
    _server(std::make_unique<Server>())
{
    time_t now = time(0);

    tm *info = localtime(&now);
    _logDirectory += 
        std::to_string(1900 + info->tm_year) + "-" + 
        std::to_string(info->tm_mon) + "-" + 
        std::to_string(info->tm_mday) + "-" +
        std::to_string(info->tm_hour) + ":" +
        std::to_string(info->tm_min) + ":" +
        std::to_string(info->tm_sec);
    std::cout << "All finish order will be send in logs/" << _logDirectory << std::endl;
}

Reception::Reception(const Reception &reception) :
    _cookingMultiplier(reception._cookingMultiplier),
    _cooksPerKitchen(reception._cooksPerKitchen),
    _regenerateTime(reception._regenerateTime),
    _server(std::make_unique<Server>(*reception._server)),
    _orders(reception._orders),
    _logDirectory(reception._logDirectory)
{
}

Reception &Reception::operator=(const Reception &reception)
{
    _cookingMultiplier = reception._cookingMultiplier;
    _cooksPerKitchen = reception._cooksPerKitchen;
    _regenerateTime = reception._regenerateTime;
    _server = std::make_unique<Server>(*reception._server);
    _orders = reception._orders;
    _logDirectory = reception._logDirectory;
    return (*this);
}

void Reception::run()
{
    std::string command;
    UserShell shell;

    while(shell.isShellActive()) {
        shell.update();
        command = shell.getUserCommand();
        if (!command.empty())
            translateCommand(command);
        readProcess();
    }
}

void Reception::readProcess()
{
    std::for_each(_process.begin(), _process.end(), [this](std::shared_ptr<IProcess> &process) {
        process->read();
        std::string data = process->getData();
        if (data.size() == 0)
            return;
        this->translateFinishOrder(data);
    });
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
        throw ReceptionError("Invalid reply from the client", "tranlateFinishOrder");
    nOrderStr = nextStrFinishOrder(order, i);
    typeStr = nextStrFinishOrder(order, i);
    sizeStr = nextStrFinishOrder(order, i);
    

    int nOrder = std::stoi(nOrderStr);
    IPizza::PizzaType type = Utils::getPizzaType(typeStr);
    IPizza::PizzaSize size = Utils::getPizzaSize(sizeStr);
    auto orderIt = std::find_if(_orders.begin(), _orders.end(), [&nOrder](std::shared_ptr<Order> &order) -> bool {
        return (nOrder == order->getId());
    });

    if (orderIt == _orders.end())
        throw ReceptionError("Fatal error: unable to find the order");
    (*orderIt)->addPizzaFinish(type, size);
    if ((*orderIt)->isFinish()) {
        (*orderIt)->pack(_logDirectory);
        _orders.erase(orderIt);
    }
} catch (const std::exception &e) {
    throw ReceptionError("Invalid reply for the client", "translateFinishOrder");
}

bool Reception::isStatusCommand(const std::string &command) const
{
    std::string name = "";

    for (size_t i = 0; command[i] && (command[i] == ' ' || command[i] == '\t'); i++);
    for (size_t i = 0; command[i] && command[i] != ' ' && command[i] != '\t'; i++) {
        name += command[i];
    }
    return (name == "status");
}

void Reception::sendStatus(int i)
{
    _process[i]->send("500\n");

    while (_process[i]->send() != false);
}

void Reception::waitResponseStatus(int i)
{
    std::string data = "";

    while ((data.size() == 0 || getCode(data) != 400) && _process[i]->isAlive()) {
        _process[i]->read();
        data = _process[i]->getData();
        if (!data.empty() && getCode(data) == 300)
            translateFinishOrder(data);
    }
}

void Reception::statusCommand()
{
    for (int i = 0; i < _process.size(); i++) {
        sendStatus(i);
        waitResponseStatus(i);
    }
}

void Reception::writeOrderToClient(std::shared_ptr<Order> &order, int i, const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza)
{
    _process[i]->send(std::string(std::to_string(order->getId()) + " " + Utils::getStringPizzaType(std::get<0>(pizza)) + " " + Utils::getStringPizzaSize(std::get<1>(pizza)) + "\n"));

    while (_process[i]->send() != false);
}

int Reception::getCode(const std::string &res) const
{
    std::string codeStr = "";

    for (int i = 0; res[i] != '\n' && res[i] != ' '; i++) {
        if (!(res[i] >= '0' && res[i] <= '9'))
            throw ReceptionError("Invalid code reply", "getCode");
        codeStr += res[i];
    }
    return (std::stoi(codeStr));
}

bool Reception::clientAcceptOrder(int i)
{
    std::string data = "";

    // std::cout << "{RECEPTION} waiting for client accept order..." << std::endl;
    while (data.empty() || getCode(data) != 100) {
        _process[i]->read();
        data = _process[i]->getData();
        if (!data.empty() && getCode(data) == 300)
            translateFinishOrder(data);
    }
    return data == "100 1\n";
}

void Reception::childConnection()
{
    int fd = _server->getFd();
    fd_set readfs;

    FD_ZERO(&readfs);
    FD_SET(fd, &readfs);
    if (select(FD_SETSIZE, &readfs, NULL, NULL, NULL) < 0)
        throw ReceptionError("Select fail", "childConnection");
    int newFd = _server->newConnection();
    std::shared_ptr<IProcess> process = _process[_process.size() - 1];

    process->createIPC(newFd);
    process->send("200\n");
    while (process->send() != false);
}

void Reception::translateCommand(const std::string &command)
try {
    std::shared_ptr<Order> order = std::make_shared<Order>(command, _cookingMultiplier);

    std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> pizzas = order->getPizzas();
    // std::cout << order << std::endl;

    std::cout << "[RECEPTION] Order sent to the kitchens" << std::endl;
    _orders.push_back(order);
    int a = 0;
    std::for_each(pizzas.begin(), pizzas.end(), [this, &order, &a](std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        // Find a kitchen which can accept the pizza

        for (int i = 0; i < _process.size(); i++) {
            writeOrderToClient(order, i, pizza);
            if (clientAcceptOrder(i)) {
                order->setSend(a, true);
                a++;
                return;
            }
        }
        // std::cout << "{RECEPTION}" << " no kitchen found" << std::endl;
        // Fork if no kitchen can take the pizza
        std::shared_ptr<IProcess> process = std::make_shared<Process>();

        _process.push_back(process);
        if (process->isInChild())
            kitchenProcess();
        childConnection();
        writeOrderToClient(order, _process.size() - 1, pizza);
        if (!clientAcceptOrder(_process.size() - 1))
            throw ReceptionError("Fatal error : Unable to send the pizza");
        // std::cout << "{RECEPTION} client accept order" << std::endl;
        order->setSend(a, true);
        a++;
    });

} catch (const ParserError &e) {
    std::cout << "Invalid command" << std::endl;
} catch (const ProcessError &e) {
    throw e;
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