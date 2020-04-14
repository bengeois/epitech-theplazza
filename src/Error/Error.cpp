/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <Error/Error.hpp>
#include <utility>

using namespace Plazza;

PlazzaError::PlazzaError(std::string message, std::string component) noexcept : _message(std::move(message)), _component(std::move(component))
{
}

const std::string & PlazzaError::getComponent() const noexcept
{
    return _component;
}

const char * PlazzaError::what() const noexcept
{
    return _message.c_str();
}

PlazzaError::PlazzaError(const PlazzaError &old) noexcept
{
    _message = std::string(old._message);
    _component = std::string(old._component);
}

PlazzaError &PlazzaError::operator=(const PlazzaError &rhs) noexcept
{
    if (this != &rhs) {
        _message = std::string(rhs._message);
        _component = std::string(rhs._component);
    }
    return *this;
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

UtilsError::UtilsError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

FileError::FileError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}