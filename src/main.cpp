/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Plazza.hpp"

using namespace Plazza;

int main(int argc, char **argv)
{
    try {

        std::unique_ptr<Parser> parser = std::make_unique<Parser>(argc, argv);
        parser->build();

        //std::unique_ptr<UserShell> interface = std::make_unique<UserShell>();
        //interface->run();

    } catch (const PlazzaError &e) {
        std::cout << "[PLAZZA]" << " {" << e.getComponent() << "} " << e.what() << std::endl;
        return PLAZZA_ERROR;
    }
}
