/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Pizza/APizza.hpp"

using namespace Plazza;

APizza::APizza(const std::string &name, PizzaSize size) : _name(name), _size(size)
{

}

APizza::~APizza() = default;

bool APizza::cook()
{
    return true;
}

const std::map<size_t, size_t> &APizza::getIngredient()
{
    return _ingredients;
}

IPizza::PizzaSize APizza::getSize() const
{
    return (_size);
}

const std::string &APizza::getName() const
{
    return (_name);
}

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Plazza::IPizza> &pizza)
{
    std::map<IPizza::PizzaSize, std::string> sizes;

    sizes[IPizza::PizzaSize::L] = "L";
    sizes[IPizza::PizzaSize::M] = "M";
    sizes[IPizza::PizzaSize::S] = "S";
    sizes[IPizza::PizzaSize::XL] = "XL";
    sizes[IPizza::PizzaSize::XXL] = "XXL";

    os << "Pizza " << pizza->getName() << sizes[pizza->getSize()];
    return (os);
}