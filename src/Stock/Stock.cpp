/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Stock/Stock.hpp"

using namespace Plazza;

Stock::Stock(float regenerateTime) : _regenerateTime(regenerateTime), _beginRegeneration(std::chrono::steady_clock::now())
{
    for (const auto e : Plazza::availableIngredients)
        _stock[e] = 5;
}

void Stock::regenerateIngredient()
{
    std::chrono::steady_clock::time_point endRegeneration = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(endRegeneration - _beginRegeneration).count() < _regenerateTime)
        return;

    for (const auto e : Plazza::availableIngredients)
        _stock[e] += 1;
    _beginRegeneration = std::chrono::steady_clock::now();
}

void Stock::reserveIngredient(const std::shared_ptr<IPizza> &pizza)
{
    for (std::pair<size_t, size_t> ingredient : pizza->getIngredient())
        _stock.at(ingredient.first) -= ingredient.second;
}

bool Stock::canCookPizza(const std::shared_ptr<IPizza> &pizza) const
{
    for (std::pair<size_t, size_t> ingredient : pizza->getIngredient()) {
        if (_stock.at(ingredient.first) < ingredient.second)
            return false;
    }
    return true;
}

void Stock::setRegenerateTime(float regenerateTime)
{
    _regenerateTime = regenerateTime;
}

float Stock::getRegenerateTime() const
{
    return _regenerateTime;
}
