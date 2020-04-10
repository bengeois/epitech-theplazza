/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_IPIZZA_HPP
#define CPP_PLAZZA_2019_IPIZZA_HPP

namespace Plazza
{
    class IPizza
    {
        public:
            enum PizzaType
            {
                Regina = 1,
                Margarita = 2,
                Americana = 4,
                Fantasia = 8,
            };

            enum PizzaSize
            {
                S = 1,
                M = 2,
                L = 4,
                XL = 8,
                XXL = 16,
            };
        
        public:
            virtual ~IPizza() = default;

            virtual bool cook() = 0;
            virtual void getIngredient() = 0;
    };
}

#endif //CPP_PLAZZA_2019_IPIZZA_HPP
