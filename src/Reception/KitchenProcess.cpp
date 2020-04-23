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

void Reception::connectKitchen(std::shared_ptr<IIPC> &client)
{
    fd_set writefs;
    fd_set readfs;

    FD_ZERO(&writefs);
    FD_ZERO(&readfs);

    // Connection to server
    while (client->getData() != "200\n") {
        client->read();
    }
}

void Reception::kitchenProcess()
{
    std::shared_ptr<IIPC> client = std::make_shared<Socket>();
    std::shared_ptr<Kitchen> kitchen = std::make_shared<Kitchen>(_cooksPerKitchen, _regenerateTime, _cookingMultiplier);

    try {
        connectKitchen(client);
        client->read();
        std::cout << "New kitchen create. ID = " << kitchen->getID() << std::endl;
        kitchen->run(client);
    } catch (const PlazzaError &e) {
        std::cout << "[PLAZZA]" << " {" << e.getComponent() << "} " << e.what() << std::endl;
        exit(PLAZZA_ERROR);
    }
    exit(0);
}