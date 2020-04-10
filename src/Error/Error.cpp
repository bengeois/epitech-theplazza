/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <Error/Error.hpp>

using namespace Plazza;

PlazzaError::PlazzaError(const std::string &message, const std::string &component) : _message(message), _component(component)
{
}

const std::string & PlazzaError::getComponent() const
{
    return _component;
}

const char * PlazzaError::what() const noexcept
{
    return _message.c_str();
}

ParserError::ParserError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

ReceptionError::ReceptionError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

UserShellError::UserShellError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

KitchenError::KitchenError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

ServerError::ServerError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

ClientError::ClientError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

OrderError::OrderError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}