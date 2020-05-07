/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Utils
*/

#include "Utils.hpp"
#include "Error/Error.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>

using namespace Plazza;

std::string Utils::toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return (std::tolower(c));
    });
    return (str);
}

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

const std::string Utils::getStringIngredient(Ingredient type)
{
    std::map<Ingredient, std::string> types = {
        {DOE, "DOE"},
        {TOMATO, "TOMATO"},
        {GRUYERE, "GRUYERE"},
        {HAM, "HAM"},
        {MUSHROOMS, "MUSHROOMS"},
        {STEAK, "STEAK"},
        {EGGPLANT, "EGGPLANT"},
        {GOAT_CHEESE, "GOAT_CHEESE"},
        {CHIEF_LOVE, "CHIEF_LOVE"},
    };

    types.count(type);
    if (!types.count(type))
        throw UtilsError("Index out of range", "getStringIngredient");
    return (types[type]);
}

bool Utils::blockRead(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return false;
    flags &= ~O_NONBLOCK;
    return fcntl(fd, F_SETFL, flags) != 1;
}

bool Utils::unblockRead(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return false;
    flags |= O_NONBLOCK;
    return fcntl(fd, F_SETFL, flags) != 1;
}