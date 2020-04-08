/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <Error.hpp>

using namespace Plazza;

/*
 * MAIN CLASS ERROR
 */

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

/*
 * PARSER CLASS ERROR
 */

ParserError::ParserError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

/*
 * USERSHELL CLASS ERROR
 */

UserShellError::UserShellError(const std::string &message, const std::string &component) : PlazzaError(message, component)
{
}

