/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Plazza.hpp"
#include "UserShell/UserShell.hpp"

using namespace Plazza;

int main(void)
{
    UserShell shell;
    std::string line;

    while(shell.isShellActive()) {
        shell.update();
        //std::cout << "test" << std::endl;
        line = shell.getUserCommand();
        if (!line.empty())
            std::cout << line << std::endl;
    }
}