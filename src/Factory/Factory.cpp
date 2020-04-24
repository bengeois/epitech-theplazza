/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Factory
*/

#include "Factory/Factory.hpp"

using namespace Plazza;

Factory::Factory(int arg1, int arg2, IIPC::IPCType type) : _type(type), _arg1(arg1), _arg2(arg2)
{
}

Factory::~Factory()
{
}

std::shared_ptr<IIPC> Factory::createIPC() const
{
    std::map<IIPC::IPCType, std::shared_ptr<IIPC> (Factory::*)() const> ipcs = {
        {IIPC::SOCKET, &Factory::createSocket}
    };

    return (this->*ipcs[_type])();
}

std::shared_ptr<IIPC> Factory::createSocket() const
{
    return (std::make_shared<Socket>(_arg1, _arg2));
}