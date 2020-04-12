/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include <sstream>
#include "Parser/Parser.hpp"

Plazza::Parser::Parser(int argc, char **argv) try : _argv(std::vector<std::string>(argv + 1, argv + argc)),
_cookingMultiplier(0),
_cooksPerKitchen(0),
_regenerateTime(0)
{
} catch (const std::exception &e) {
    throw ParserError("Invalid number of argument.", "Parser");
}

void Plazza::Parser::build()
{
    if (_argv.empty() || _argv.size() != 3)
        throw ParserError("Invalid number of argument.", "Parser");

    if ((std::istringstream(_argv[0]) >> _cookingMultiplier).fail()
    || (std::istringstream(_argv[1]) >> _cooksPerKitchen).fail()
    || (std::istringstream(_argv[2]) >> _regenerateTime).fail())
        throw ParserError("Bad argument.", "Parser");

    if (_cooksPerKitchen < 1)
        throw ParserError("Must be 1 cook per kitchen minimum", "Parser");
}

long Plazza::Parser::getCookingMultiplier() const
{
    return _cookingMultiplier;
}

int Plazza::Parser::getCooksPerKitchen() const
{
    return _cooksPerKitchen;
}

float Plazza::Parser::getRegenerateTime() const
{
    return _regenerateTime;
}