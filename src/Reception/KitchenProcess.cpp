/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Plazza.hpp"

using namespace Plazza;

void Reception::connectKitchen(std::shared_ptr<Client> &client)
{
    fd_set writefs;
    fd_set readfs;

    FD_ZERO(&writefs);
    FD_ZERO(&readfs);

    // Connection to server
    while (client->getData() != "200\n") {
        resetFdSet(&readfs, &writefs);
        client->setFdSet(&readfs, &writefs);
        if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
            throw ReceptionError("Select fail", "Select");
        client->translateSelect(readfs, writefs);
    }
    std::cout << "New kitchen create" << std::endl;
}

void Reception::kitchenProcess()
{
    std::shared_ptr<Client> client = std::make_shared<Client>(_server->getPort());
    std::shared_ptr<Kitchen> kitchen = std::make_shared<Kitchen>(_cooksPerKitchen, _regenerateTime);

    try {
        connectKitchen(client);
        client->makeBlocking();
        kitchen->run(client);
    } catch (const PlazzaError &e) {
        std::cout << "[PLAZZA]" << " {" << e.getComponent() << "} " << e.what() << std::endl;
        exit(PLAZZA_ERROR);
    }
    exit(0);
}