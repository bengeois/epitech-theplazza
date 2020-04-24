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
#include "LocalTime/LocalTime.hpp"

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace Plazza;

Reception::Reception(long cookingMultiplier, int cooksPerKitchen, float
regenerateTime, IIPC::IPCType type) :
    _cookingMultiplier(cookingMultiplier),
    _cooksPerKitchen(cooksPerKitchen),
    _regenerateTime(regenerateTime),
    _type(type)
{
    if (_type == IIPC::SOCKET)
        _server = std::make_unique<Server>();
    createLogDirectory();
}


/****************\

Coplien form

\****************/

Reception::Reception(const Reception &reception) :
    _cookingMultiplier(reception._cookingMultiplier),
    _cooksPerKitchen(reception._cooksPerKitchen),
    _regenerateTime(reception._regenerateTime),
    _orders(reception._orders),
    _logDirectory(reception._logDirectory)
{
    if (reception._server != nullptr)
        _server = std::make_unique<Server>(*reception._server);
}

Reception &Reception::operator=(const Reception &reception)
{
    _cookingMultiplier = reception._cookingMultiplier;
    _cooksPerKitchen = reception._cooksPerKitchen;
    _regenerateTime = reception._regenerateTime;
    if (reception._server != nullptr)
        _server = std::make_unique<Server>(*reception._server);
    _orders = reception._orders;
    _logDirectory = reception._logDirectory;
    return (*this);
}


/****************\

Public methods

\****************/

void Reception::run()
{
    std::string command;
    UserShell shell;

    while(shell.isShellActive()) {
        shell.update();
        command = shell.getUserCommand();
        if (!command.empty()) {
            if (isStatusCommand(command))
                statusCommand();
            else
                translateCommand(command);
        }
        clearProcess();
        readProcess();
    }
}


/****************\

Private methods

\****************/

void Reception::createLogDirectory()
{
    LocalTime time;

    _logDirectory += 
        std::to_string(time.getHour()) + "-" + 
        std::to_string(time.getMonth()) + "-" + 
        std::to_string(time.getDay()) + "-" +
        std::to_string(time.getHour()) + ":" +
        std::to_string(time.getMin()) + ":" +
        std::to_string(time.getSec());
    std::cout << "All finish order will be send in logs/" << _logDirectory << std::endl;
}


/****************\

Processus management methods

\****************/

/**
 * Read data which come to kitchens
*/
void Reception::readProcess()
{
    std::for_each(_process.begin(), _process.end(), [this](std::shared_ptr<IProcess> &process) {
        process->read();
        std::string data = process->getData();
        if (data.empty())
            return;
        this->translateDataKitchen(data);
    });
}

/**
 * Clear processus if there are ending
*/
void Reception::clearProcess()
{
    _process.erase(std::remove_if(_process.begin(), _process.end(), [](const std::shared_ptr<IProcess> &client) {
        return (!client->isAlive());
    }), _process.end());
}

const std::string Reception::nextStrDataKitchen(const std::string &order, size_t &i) const
{
    if (order[i] == ' ')
        i++;
    std::string data = "";
    for (; order[i] != '\n' && order[i] != ' '; i++) {
        data += order[i];
    }
    return (data);
}

/**
 * Translate data which come to kitchen, this data represent a finish pizza
 */
void Reception::translateDataKitchen(const std::string &order)
try {
    std::string nOrderStr = "";
    std::string typeStr = "";
    std::string sizeStr = "";
    size_t i = 4;

    if (order.size() <= 4)
        throw ReceptionError("Invalid reply from the client", "tranlateFinishOrder");
    nOrderStr = nextStrDataKitchen(order, i);
    typeStr = nextStrDataKitchen(order, i);
    sizeStr = nextStrDataKitchen(order, i);

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

/****************\

End of processus management methods

\****************/



/****************\

Start of user new order command

\****************/

void Reception::translateCommand(const std::string &command)
try {
    std::shared_ptr<Order> order = std::make_shared<Order>(command, _cookingMultiplier);

    std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> pizzas = order->getPizzas();

    std::cout << "[RECEPTION] Order sent to the kitchens" << std::endl;
    _orders.push_back(order);
    int a = 0;
    std::for_each(pizzas.begin(), pizzas.end(), [this, &order, &a](std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {

        // Find a kitchen which can accept the pizza
        for (int i = 0; static_cast<size_t>(i) < _process.size(); i++) {
            writeOrderToClient(order, i, pizza);
            if (clientAcceptOrder(i)) {
                order->setSend(a, true);
                a++;
                return;
            }
        }
        // Fork if no kitchen can take the pizza
        std::shared_ptr<IProcess> process = std::make_shared<Process>();

        _process.push_back(process);
        if (process->isInChild())
            kitchenProcess();
        childConnection();
        writeOrderToClient(order, _process.size() - 1, pizza);
        if (!clientAcceptOrder(_process.size() - 1))
            throw ReceptionError("Fatal error : Unable to send the pizza");
        order->setSend(a, true);
        a++;
    });

} catch (const ParserError &e) {
    std::cout << "Invalid command" << std::endl;
} catch (const ProcessError &e) {
    throw e;
}

void Reception::writeOrderToClient(std::shared_ptr<Order> &order, int i, const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza)
{
    _process[i]->send(std::string(std::to_string(order->getId()) + " " + Utils::getStringPizzaType(std::get<0>(pizza)) + " " + Utils::getStringPizzaSize(std::get<1>(pizza)) + "\n"));

    while (_process[i]->send());
}

int Reception::getCode(const std::string &res) const
{
    std::string codeStr;

    for (int i = 0; res[i] != '\n' && res[i] != ' '; i++) {
        if (!(res[i] >= '0' && res[i] <= '9'))
            throw ReceptionError("Invalid code reply", "getCode");
        codeStr += res[i];
    }
    return (std::stoi(codeStr));
}

bool Reception::clientAcceptOrder(int i)
{
    std::string data;

    while (data.empty() || getCode(data) != 100) {
        _process[i]->read();
        data = _process[i]->getData();
        if (!data.empty() && getCode(data) == 300)
            translateDataKitchen(data);
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

    process->createIPC(-1, newFd, _type);
    process->send("200\n");
    while (process->send());
}

/****************\

End of user new order command

\****************/


/****************\

Start of user status command

\****************/

bool Reception::isStatusCommand(const std::string &command) const
{
    std::string name;

    for (size_t i = 0; command[i] && (command[i] == ' ' || command[i] == '\t'); i++);
    for (size_t i = 0; command[i] && command[i] != ' ' && command[i] != '\t'; i++) {
        name += command[i];
    }
    return (name == "status\n");
}

void Reception::sendStatus(int i)
{
    _process[i]->send("500\n");

    while (_process[i]->send());
}

void Reception::waitResponseStatus(int i)
{
    std::string data;

    while ((data.empty() || getCode(data) != 400) && _process[i]->isAlive()) {
        _process[i]->read();
        data = _process[i]->getData();
        if (!data.empty() && getCode(data) == 300)
            translateDataKitchen(data);
    }
}

void Reception::statusCommand()
{
    for (int i = 0; static_cast<size_t>(i) < _process.size(); i++) {
        sendStatus(i);
        waitResponseStatus(i);
    }
}

/****************\

End of user status command

\****************/


/****************\

Start getter and setter

\****************/

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

/****************\

End getter and setter

\****************/