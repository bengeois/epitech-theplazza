/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Pizza/APizza.hpp"

using namespace Plazza;

APizza::APizza(PizzaType type, PizzaSize size, long cookingMultiplier) : _type(type), _size(size), _cookingMultiplier(cookingMultiplier)
{
}

const std::map<size_t, size_t> &APizza::getIngredient()
{
    return _ingredients;
}

IPizza::PizzaSize APizza::getSize() const
{
    return _size;
}

IPizza::PizzaType APizza::getType() const
{
    return _type;
}

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Plazza::IPizza> &pizza)
{
    std::map<IPizza::PizzaSize, std::string> sizes;

    sizes[IPizza::PizzaSize::L] = "L";
    sizes[IPizza::PizzaSize::M] = "M";
    sizes[IPizza::PizzaSize::S] = "S";
    sizes[IPizza::PizzaSize::XL] = "XL";
    sizes[IPizza::PizzaSize::XXL] = "XXL";

    os << "Pizza " << pizza->getType() << " " << sizes[pizza->getSize()];
    return (os);
}