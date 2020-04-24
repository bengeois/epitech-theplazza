/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Plazza.hpp"
#include "Factory/Factory.hpp"

using namespace Plazza;

void Reception::connectKitchen(std::shared_ptr<IIPC> client)
{
    fd_set writefs;
    fd_set readfs;

    FD_ZERO(&writefs);
    FD_ZERO(&readfs);

    // Connection to server
    // std::cout << "{CHILD} waiting for 200 connection" << std::endl;
    while (client->getData() != "200\n") {
        // std::cout << "{CHILD} getData : " + client->getData() << std::endl;
        client->read();
    }
    // std::cout << "{CHILD} waiting receive 200 connection" << std::endl;
}

void Reception::kitchenProcess(std::shared_ptr<IProcess> &process)
try {
    if (_type == IIPC::SOCKET) {
        process->createIPC(_server->getPort(), -1, IIPC::SOCKET);
        connectKitchen(process->getIpc());
    }
    std::shared_ptr<Kitchen> kitchen = std::make_shared<Kitchen>(_cooksPerKitchen, _regenerateTime, _cookingMultiplier);

    process->read();
    std::cout << "New kitchen create. ID = " << kitchen->getID() << std::endl;
    kitchen->run(process->getIpc());
    exit(0);

} catch(const PlazzaError &e) {
    std::cout << "[PLAZZA]" << " {" << e.getComponent() << "} " << e.what() << std::endl;
    exit(PLAZZA_ERROR);
}