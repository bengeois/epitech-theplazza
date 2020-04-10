/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_APIZZA_HPP
#define CPP_PLAZZA_2019_APIZZA_HPP

#include "IPizza.hpp"

namespace Plazza
{
    class APizza : public IPizza
    {
        public:
            APizza(const std::string &name, PizzaSize size);
            ~APizza() override;

            bool cook() override;
            const std::map<size_t, size_t> &getIngredient() override;

            PizzaSize getSize() const override;
            const std::string &getName() const override;

        private:
            const std::string _name;
            PizzaSize _size;
            std::map<size_t, size_t> _ingredients;

    };
}

#endif //CPP_PLAZZA_2019_APIZZA_HPP
