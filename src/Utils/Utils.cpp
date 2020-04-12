/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Utils
*/

#include "Utils.hpp"
#include "Error/Error.hpp"

using namespace Plazza;

const std::string Utils::getStringPizzaType(IPizza::PizzaType type)
{
    std::map<IPizza::PizzaType, std::string> types = {
        {IPizza::Regina, "regina"},
        {IPizza::Margarita, "margarita"},
        {IPizza::Americana, "americana"},
        {IPizza::Fantasia, "fantasia"},
    };

    if (!types.count(type))
        throw UtilsError("Index out of range", "getStringPizzaType");
    return (types[type]);
}

const std::string Utils::getStringPizzaSize(IPizza::PizzaSize size)
{
    std::map<IPizza::PizzaSize, std::string> sizes = {
        {IPizza::S, "S"},
        {IPizza::M, "M"},
        {IPizza::L, "L"},
        {IPizza::XL, "XL"},
        {IPizza::XXL, "XXL"},
    };

    if (!sizes.count(size))
        throw UtilsError("Index out of range", "getStringPizzaSize");
    return (sizes[size]);
}

IPizza::PizzaType Utils::getPizzaType(const std::string &type)
{
    std::map<std::string, IPizza::PizzaType> types = {
        {"regina", IPizza::Regina},
        {"margarita", IPizza::Margarita},
        {"americana", IPizza::Americana},
        {"fantasia", IPizza::Fantasia},
    };

    if (!types.count(type))
        throw UtilsError("Index out of range", "getPizzaType");
    return (types[type]);
}

IPizza::PizzaSize Utils::getPizzaSize(const std::string &size)
{
    std::map<std::string, IPizza::PizzaSize> sizes = {
        {"S", IPizza::S},
        {"M", IPizza::M},
        {"L", IPizza::L},
        {"XL", IPizza::XL},
        {"XXL", IPizza::XXL},
    };

    if (!sizes.count(size))
        throw UtilsError("Index out of range", "getPizzaSize");
    return (sizes[size]);
}